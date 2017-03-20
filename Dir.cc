#include <algorithm>
#include <string>
#include <vector>

#include <dirent.h>
#include <sys/types.h>

using namespace std;
using namespace cpad;

Dir::Dir()
  : Dir(".")
{
}
    
Dir::Dir(string pathname)
  : m_name(pathname),
    m_recursive(false)
{
}
    
Dir::Dir(Dir const& a_copy)
{
  m_name = a_copy.m_name;
}
    
Dir::~Dir(void)
{

}
Dir& Dir::operator =(Dir const &a_copy)
{
  m_name = a_copy.m_name;
}
    
const char *
Dir::get_pathname(void)
{
  return m_name.c_str();
}
    
vector<string>
read_directory(enum DirReadFlags flags)
{
  vector <string> result;
  dirent* de;
  DIR* dp;
  errno = 0;
  dp = opendir( m_pathname.empty() ? "." : m_pathname.c_str() );
  if (dp)
    {
      while (true)
        {
          errno = 0;
          de = readdir( dp );
          if (de == NULL) break;
          if (flags & READ_DIR_INCLUDE_DOTS &&
              string(".").compare(de->d_name) &&
              string("..").compare(de->d_name))
            result.push_back( std::string( de->d_name ) );
        }
      closedir( dp );
      if (flags & READ_DIR_SORT)
        std::sort( result.begin(), result.end() );
    }
  return result;
}
