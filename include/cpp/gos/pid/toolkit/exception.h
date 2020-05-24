/*****************************************************************//**
 * \file   exception.h
 * \brief  PID Toolkit Exception class include file.
 * 
 * \author Geirmundur Orri Sigurdsson
 * \date   May 2020
 *********************************************************************/
#ifndef GOS_PID_TOOLKIT_EXCEPTION_H_
#define GOS_PID_TOOLKIT_EXCEPTION_H_

#include <string>
#include <exception>

namespace gos {
namespace pid {
namespace toolkit {

//!  PID Toolkit Exception class. 
/*!
  The PID Toolkit Exception.
*/
class exception : public std::exception {
public:
  //! The constructor.
  /*!
    Constructs a PID Toolkit exception.
    \param what The description of the exception cause.
  */
  exception(const char* what);
#if _MSC_VER >= 1910
  const char* what() const noexcept override;
#else
  const char* what() const;
#endif
private:
  std::string what_;
};

} // namespace toolkit
} // namespace pid
} // namespace gos

#endif
