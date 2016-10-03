//
// Created by frasse_l on 03/10/2016.
//

#ifndef INC_302POIGNEES_USER_HH
# define INC_302POIGNEES_USER_HH

# include <string>
# include <vector>

class User
{
public:
    User(const std::string &);
    ~User();
    const std::string &getName() const;
    const std::vector<User *> &getLinks() const;
    void addLink(User *);
private:
    std::string _name;
    std::vector<User *> _links;
};

#endif //INC_302POIGNEES_USER_HH
