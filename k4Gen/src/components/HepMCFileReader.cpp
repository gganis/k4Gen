
#include "HepMCFileReader.h"
#include "HepMC3/ReaderAscii.h"
#include "HepMC3/ReaderAsciiHepMC2.h"
#include "HepMC3/ReaderLHEF.h"

#include "GaudiKernel/IEventProcessor.h"
#include "GaudiKernel/IIncidentSvc.h"
#include "GaudiKernel/Incident.h"

DECLARE_COMPONENT(HepMCFileReader)

HepMCFileReader::HepMCFileReader(const std::string& type, const std::string& name, const IInterface* parent)
: GaudiTool(type, name, parent), m_file(nullptr) {
  declareInterface<IHepMCProviderTool>(this);
}

HepMCFileReader::~HepMCFileReader() { ; }

StatusCode HepMCFileReader::initialize() {
  if (m_filename.empty()) {
    error() << "Input file name is not specified!" << endmsg;
    return StatusCode::FAILURE;
  }
  // open file using HepMC routines
  info() << "Initialising for format: " << m_format.value() << endmsg;
  if (m_format.value().compare("hepmc2") == 0) {
     info() << "Initialising m_info with HepMC3::ReaderAsciiHepMC2 " << endmsg;
     m_file = std::make_unique<HepMC3::ReaderAsciiHepMC2>(m_filename.value());
  } else if (m_format.value().compare("lhef") == 0) {
     info() << "Initialising m_info with HepMC3::ReaderLHEF " << endmsg;
     m_file = std::make_unique<HepMC3::ReaderLHEF>(m_filename.value());
  } else {
     info() << "Initialising m_info with HepMC3::ReaderAscii " << endmsg;
     m_file = std::make_unique<HepMC3::ReaderAscii>(m_filename.value());
  }
  StatusCode sc = GaudiTool::initialize();
  return sc;
}

StatusCode HepMCFileReader::getNextEvent(HepMC3::GenEvent& event) {
  if (!m_file->read_event(event)) {
    error() << "Premature end of file: Please set the number of events according to hepMC file." << endmsg;
    return Error("Reached end of file before finished processing");
  }
  return StatusCode::SUCCESS;
}

StatusCode HepMCFileReader::finalize() {
  m_file.reset();
  return GaudiTool::finalize();
}
