//
// Copyright ©2017 NagraFrance
//

#include "CompilationUnitMsg.h"

//
// CompilationUnitStart helpers implem
//

/**
 * Constructor
 */
cpad::cfg::CompilationUnitStartRequestHelper::CompilationUnitStartRequestHelper(std::string filename)
  : ::cpad::cfg::CompilationUnitStartRequest()
{
  set_filename(filename);
}

/**
 * Deserialize constructor
 */
cpad::cfg::CompilationUnitStartRequestHelper::CompilationUnitStartRequestHelper(const char *buffer)
  : ::cpad::cfg::CompilationUnitStartRequest()
{
  ParseFromString(std::string(buffer));
}

/**
 * Constructor from request
 */
cpad::cfg::CompilationUnitStartRequestHelper::CompilationUnitStartRequestHelper(const ::cpad::cfg::CompilationUnitStartRequest* request)
  : ::cpad::cfg::CompilationUnitStartRequest(*request)
{
}

/**
 * Desctructor
 */
cpad::cfg::CompilationUnitStartRequestHelper::~CompilationUnitStartRequestHelper()
{
}

/**
 * Copy constructor
 */
cpad::cfg::CompilationUnitStartRequestHelper::CompilationUnitStartRequestHelper(cpad::cfg::CompilationUnitStartRequestHelper const&a_copy)
  : cpad::cfg::CompilationUnitStartRequestHelper(a_copy.filename())
{
}

/**
 * Affectation Operator
 */
cpad::cfg::CompilationUnitStartRequestHelper&
cpad::cfg::CompilationUnitStartRequestHelper::operator =(cpad::cfg::CompilationUnitStartRequestHelper const&a_copy)
{
  set_filename(a_copy.filename());
  return *this;
}

/**
 * Serialize helper method
 */
size_t
cpad::cfg::CompilationUnitStartRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

/**
 * Dump helper method
 */
void
cpad::cfg::CompilationUnitStartRequestHelper::dump(std::ostream& osb)
{
  osb << "[CompilationUnitStartRequest]" << std::endl;
  osb << "CUnit filename: " << filename() << std::endl;
}

cpad::cfg::CompilationUnitStartResponseHelper::CompilationUnitStartResponseHelper()
  : ::cpad::cfg::CompilationUnitStartResponse()
{
}

cpad::cfg::CompilationUnitStartResponseHelper::CompilationUnitStartResponseHelper(const char *buffer)
  : ::cpad::cfg::CompilationUnitStartResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::CompilationUnitStartResponseHelper::CompilationUnitStartResponseHelper(const ::cpad::cfg::CompilationUnitStartResponse* response)
  : ::cpad::cfg::CompilationUnitStartResponse(*response)
{
}

cpad::cfg::CompilationUnitStartResponseHelper::~CompilationUnitStartResponseHelper()
{
}

cpad::cfg::CompilationUnitStartResponseHelper::CompilationUnitStartResponseHelper(cpad::cfg::CompilationUnitStartResponseHelper const&a_copy)
  : cpad::cfg::CompilationUnitStartResponseHelper()
{
}

cpad::cfg::CompilationUnitStartResponseHelper&
cpad::cfg::CompilationUnitStartResponseHelper::operator =(cpad::cfg::CompilationUnitStartResponseHelper const&a_copy)
{
  return *this;
}

size_t
cpad::cfg::CompilationUnitStartResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::cfg::CompilationUnitStartResponseHelper::dump(std::ostream& osb)
{
  osb << "[CompilationUnitStartResponse]" << std::endl;
}

//
// CompilationUnitEnd helpers implem
//

cpad::cfg::CompilationUnitEndRequestHelper::CompilationUnitEndRequestHelper()
  : ::cpad::cfg::CompilationUnitEndRequest()
{
}

cpad::cfg::CompilationUnitEndRequestHelper::CompilationUnitEndRequestHelper(const char *buffer)
  : ::cpad::cfg::CompilationUnitEndRequest()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::CompilationUnitEndRequestHelper::CompilationUnitEndRequestHelper(const ::cpad::cfg::CompilationUnitEndRequest* request)
  : ::cpad::cfg::CompilationUnitEndRequest(*request)
{
}

cpad::cfg::CompilationUnitEndRequestHelper::~CompilationUnitEndRequestHelper()
{
}

cpad::cfg::CompilationUnitEndRequestHelper::CompilationUnitEndRequestHelper(cpad::cfg::CompilationUnitEndRequestHelper const&a_copy)
  : cpad::cfg::CompilationUnitEndRequestHelper()
{
}

cpad::cfg::CompilationUnitEndRequestHelper&
cpad::cfg::CompilationUnitEndRequestHelper::operator =(cpad::cfg::CompilationUnitEndRequestHelper const&a_copy)
{
  return *this;
}

size_t
cpad::cfg::CompilationUnitEndRequestHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::cfg::CompilationUnitEndRequestHelper::dump(std::ostream& osb)
{
  osb << "[CompilationUnitEndRequest]" << std::endl;
}

cpad::cfg::CompilationUnitEndResponseHelper::CompilationUnitEndResponseHelper()
  : ::cpad::cfg::CompilationUnitEndResponse()
{
}

cpad::cfg::CompilationUnitEndResponseHelper::CompilationUnitEndResponseHelper(const char *buffer)
  : ::cpad::cfg::CompilationUnitEndResponse()
{
  ParseFromString(std::string(buffer));
}

cpad::cfg::CompilationUnitEndResponseHelper::CompilationUnitEndResponseHelper(const ::cpad::cfg::CompilationUnitEndResponse* response)
  : ::cpad::cfg::CompilationUnitEndResponse(*response)
{
}

cpad::cfg::CompilationUnitEndResponseHelper::~CompilationUnitEndResponseHelper()
{
}

cpad::cfg::CompilationUnitEndResponseHelper::CompilationUnitEndResponseHelper(cpad::cfg::CompilationUnitEndResponseHelper const&a_copy)
  : cpad::cfg::CompilationUnitEndResponseHelper()
{
}

cpad::cfg::CompilationUnitEndResponseHelper&
cpad::cfg::CompilationUnitEndResponseHelper::operator =(cpad::cfg::CompilationUnitEndResponseHelper const&a_copy)
{
  return *this;
}

size_t
cpad::cfg::CompilationUnitEndResponseHelper::serialize(char *buffer)
{
  std::string local_buf;
  SerializeToString(&local_buf);
  local_buf.copy(buffer, local_buf.length());
  return local_buf.length();
}

void
cpad::cfg::CompilationUnitEndResponseHelper::dump(std::ostream& osb)
{
  osb << "[CompilationUnitEndResponse]" << std::endl;
}

