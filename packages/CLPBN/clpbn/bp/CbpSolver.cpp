#include "CbpSolver.h"


CbpSolver::CbpSolver (const FactorGraph& fg) : BpSolver (fg)
{
  unsigned nrGroundVars, nrGroundFacs, nrNeighborless;
  if (Constants::COLLECT_STATS) {
    nrGroundVars = fg_->varNodes().size();
    nrGroundFacs = fg_->facNodes().size();
    const VarNodes& vars = fg_->varNodes();
    nrNeighborless = 0;
    for (unsigned i = 0; i < vars.size(); i++) {
      const FacNodes& factors = vars[i]->neighbors();
      if (factors.size() == 1 && factors[0]->neighbors().size() == 1) {
        nrNeighborless ++;
      }
    }
  }
  cfg_ = new CFactorGraph (fg);
  fg_  = cfg_->getGroundFactorGraph();
  if (Constants::COLLECT_STATS) {
    unsigned nrClusterVars = fg_->varNodes().size();
    unsigned nrClusterFacs = fg_->facNodes().size();
    Statistics::updateCompressingStatistics (nrGroundVars,
        nrGroundFacs, nrClusterVars, nrClusterFacs, nrNeighborless);
  }
  // cout << "uncompressed factor graph:" << endl;
  // cout << "  " << fg.nrVarNodes() << " variables " << endl;
  // cout << "  " << fg.nrFacNodes() << " factors "   << endl;
  // cout << "compressed factor graph:" << endl;
  // cout << "  " << fg_->nrVarNodes() << " variables " << endl;
  // cout << "  " << fg_->nrFacNodes() << " factors "   << endl;
  // Util::printHeader ("Compressed Factor Graph");
  // fg_->print();
  // Util::printHeader ("Uncompressed Factor Graph");
  // fg.print();
}



CbpSolver::~CbpSolver (void)
{
  delete cfg_;
  delete fg_;
  for (unsigned i = 0; i < links_.size(); i++) {
    delete links_[i];
  }
  links_.clear();
}



void
CbpSolver::printSolverFlags (void) const
{
  stringstream ss;
  ss << "counting bp [" ;
  ss << "schedule=" ;
  typedef BpOptions::Schedule Sch;
  switch (BpOptions::schedule) {
    case Sch::SEQ_FIXED:    ss << "seq_fixed";    break;
    case Sch::SEQ_RANDOM:   ss << "seq_random";   break;
    case Sch::PARALLEL:     ss << "parallel";     break;
    case Sch::MAX_RESIDUAL: ss << "max_residual"; break;
  }
  ss << ",max_iter=" << BpOptions::maxIter;
  ss << ",accuracy=" << BpOptions::accuracy;
  ss << ",log_domain=" << Util::toString (Globals::logDomain);
  ss << ",order_vars=" << Util::toString (FactorGraph::orderVars);
  ss << ",chkif=" << 
      Util::toString (CFactorGraph::checkForIdenticalFactors);
  ss << "]" ;
  cout << ss.str() << endl;
}



Params
CbpSolver::getPosterioriOf (VarId vid)
{
  if (runned_ == false) {
    runSolver();
  }
  assert (cfg_->getEquivalentVariable (vid));
  VarNode* var = cfg_->getEquivalentVariable (vid);
  Params probs;
  if (var->hasEvidence()) {
    probs.resize (var->range(), LogAware::noEvidence());
    probs[var->getEvidence()] = LogAware::withEvidence();
  } else {
    probs.resize (var->range(), LogAware::multIdenty());
    const SpLinkSet& links = ninf(var)->getLinks();
    if (Globals::logDomain) {
      for (unsigned i = 0; i < links.size(); i++) {
        CbpSolverLink* l = static_cast<CbpSolverLink*> (links[i]);
        Util::add (probs, l->poweredMessage());
      }
      LogAware::normalize (probs);
      Util::fromLog (probs);
    } else {
      for (unsigned i = 0; i < links.size(); i++) {
        CbpSolverLink* l = static_cast<CbpSolverLink*> (links[i]);
        Util::multiply (probs, l->poweredMessage());
      }
      LogAware::normalize (probs);
    }
  }
  return probs;
}



Params
CbpSolver::getJointDistributionOf (const VarIds& jointVids)
{
  VarIds eqVarIds;
  for (unsigned i = 0; i < jointVids.size(); i++) {
    VarNode* vn = cfg_->getEquivalentVariable (jointVids[i]);
    eqVarIds.push_back (vn->varId());
  }
  return BpSolver::getJointDistributionOf (eqVarIds);
}



void
CbpSolver::createLinks (void)
{
  const FacClusters& fcs = cfg_->facClusters();
  for (unsigned i = 0; i < fcs.size(); i++) {
    const VarClusters& vcs = fcs[i]->varClusters();
    for (unsigned j = 0; j < vcs.size(); j++) {
      unsigned c = cfg_->getEdgeCount (fcs[i], vcs[j]);
      links_.push_back (new CbpSolverLink (
          fcs[i]->getRepresentative(),
          vcs[j]->getRepresentative(), c));
    }
  }
}



void
CbpSolver::maxResidualSchedule (void)
{
  if (nIters_ == 1) {
    for (unsigned i = 0; i < links_.size(); i++) {
      calculateMessage (links_[i]);
      SortedOrder::iterator it = sortedOrder_.insert (links_[i]);
      linkMap_.insert (make_pair (links_[i], it));
      if (Constants::DEBUG >= 2 && Constants::DEBUG < 5) {
        cout << "calculating " << links_[i]->toString() << endl;
      }
    }
    return;
  }

  for (unsigned c = 0; c < links_.size(); c++) {
    if (Constants::DEBUG >= 2) {
      cout << endl << "current residuals:" << endl;
      for (SortedOrder::iterator it = sortedOrder_.begin();
          it != sortedOrder_.end(); it ++) {
        cout << "    " << setw (30) << left << (*it)->toString();
        cout << "residual = " << (*it)->getResidual() << endl;
      }
    }

    SortedOrder::iterator it = sortedOrder_.begin();
    SpLink* link = *it;
    if (Constants::DEBUG >= 2) {
      cout << "updating " << (*sortedOrder_.begin())->toString() << endl;
    }
    if (link->getResidual() < BpOptions::accuracy) {
      return;
    }
    link->updateMessage();
    link->clearResidual();
    sortedOrder_.erase (it);
    linkMap_.find (link)->second = sortedOrder_.insert (link);

    // update the messages that depend on message source --> destin
    const FacNodes& factorNeighbors = link->getVariable()->neighbors();
    for (unsigned i = 0; i < factorNeighbors.size(); i++) {
      const SpLinkSet& links = ninf(factorNeighbors[i])->getLinks();
      for (unsigned j = 0; j < links.size(); j++) {
        if (links[j]->getVariable() != link->getVariable()) {
          if (Constants::DEBUG >= 2 && Constants::DEBUG < 5) {
            cout << "    calculating " << links[j]->toString() << endl;
          }
          calculateMessage (links[j]);
          SpLinkMap::iterator iter = linkMap_.find (links[j]);
          sortedOrder_.erase (iter->second);
          iter->second = sortedOrder_.insert (links[j]);
        }
      }
    }
    // in counting bp, the message that a variable X sends to
    // to a factor F depends on the message that F sent to the X 
    const SpLinkSet& links = ninf(link->getFactor())->getLinks();
    for (unsigned i = 0; i < links.size(); i++) {
      if (links[i]->getVariable() != link->getVariable()) {
        if (Constants::DEBUG >= 2 && Constants::DEBUG < 5) {
          cout << "    calculating " << links[i]->toString() << endl;
        }
        calculateMessage (links[i]);
        SpLinkMap::iterator iter = linkMap_.find (links[i]);
        sortedOrder_.erase (iter->second);
        iter->second = sortedOrder_.insert (links[i]);
      }
    }
  }
}



Params
CbpSolver::getVar2FactorMsg (const SpLink* link) const
{
  Params msg;
  const VarNode* src = link->getVariable();
  const FacNode* dst = link->getFactor();
  const CbpSolverLink* l = static_cast<const CbpSolverLink*> (link);
  if (src->hasEvidence()) {
    msg.resize (src->range(), LogAware::noEvidence());
    double value = link->getMessage()[src->getEvidence()];
    msg[src->getEvidence()] = LogAware::pow (value, l->nrEdges() - 1);
  } else {
    msg = link->getMessage();
    LogAware::pow (msg, l->nrEdges() - 1);
  }
  if (Constants::DEBUG >= 5) {
    cout << "        " << "init: " << msg << " " << src->hasEvidence() << endl;
  }
  const SpLinkSet& links = ninf(src)->getLinks();
  if (Globals::logDomain) {
    for (unsigned i = 0; i < links.size(); i++) {
      if (links[i]->getFactor() != dst) {
        CbpSolverLink* l = static_cast<CbpSolverLink*> (links[i]);
        Util::add (msg, l->poweredMessage());
      }
    }
  } else {
    for (unsigned i = 0; i < links.size(); i++) {
      if (links[i]->getFactor() != dst) {
        CbpSolverLink* l = static_cast<CbpSolverLink*> (links[i]);
        Util::multiply (msg, l->poweredMessage());
        if (Constants::DEBUG >= 5) {
          cout << "        msg from " << l->getFactor()->getLabel() << ": " ;
          cout << l->poweredMessage() << endl;
        }
      }
    }
  }

  if (Constants::DEBUG >= 5) {
    cout << "        result = " << msg << endl;
  }
  return msg;
}



void
CbpSolver::printLinkInformation (void) const
{
  for (unsigned i = 0; i < links_.size(); i++) {
    CbpSolverLink* l = static_cast<CbpSolverLink*> (links_[i]); 
    cout << l->toString() << ":" << endl;
    cout << "    curr msg = " << l->getMessage() << endl;
    cout << "    next msg = " << l->getNextMessage() << endl;
    cout << "    nr edges = " << l->nrEdges() << endl;
    cout << "    powered  = " << l->poweredMessage() << endl;
    cout << "    residual = " << l->getResidual() << endl;
  }
}

