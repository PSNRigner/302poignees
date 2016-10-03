//
// Created by frasse_l on 03/10/2016.
//

#include "user.hh"

User::User(const std::string &name)
    : _name(name)
{
}

User::~User()
{
}

const std::string& User::getName() const
{
    return this->_name;
}

void User::addLink(User *user)
{
    this->_links.push_back(user);
}

const std::vector<User *>& User::getLinks() const
{
    return this->_links;
}