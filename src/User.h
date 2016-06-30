#ifndef USER_H
#define USER_H

#include <initializer_list>
#include <string>
class User {
public:
  User() = default;
  User(std::string t_userName, std::string t_userPassword,
       std::string t_userEmail, std::string t_userPhone);
  User(const User &&t_user);
  std::string getName() const;

  void setName(std::string t_name);
  std::string getPassword() const;
  void setPassword(std::string t_password);
  std::string getEmail() const;
  void setEmail(std::string t_email);
  std::string getPhone() const;
  void setPhone(std::string t_phone);

private:
  std::string m_name;
  std::string m_password;
  std::string m_email;
  std::string m_phone;
};

#endif
