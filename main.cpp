#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
#include "user.hh"

bool readFile(std::vector<User *> &users, char *path)
{
    std::ifstream stream;
    stream.open(path);
    if (!stream)
    {
        std::cerr << "Can't open file " << path << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(stream, line))
    {
        size_t n;
        int m = 0;
        if ((n = line.find(" est ami avec ")) != std::string::npos || ((++m) > 0 && (n = line.find(" est amie avec ")) != std::string::npos))
        {
            std::string user1 = line.substr(0, n);
            size_t o = m == 0 ? n + std::string(" est ami avec ").size() : n + std::string(" est amie avec ").size();
            std::string user2 = line.substr(o, line.size() - o);

            User *userInstance1 = NULL;
            User *userInstance2 = NULL;
            for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
                if ((*it)->getName() == user1)
                    userInstance1 = *it;
                else if ((*it)->getName() == user2)
                    userInstance2 = *it;

            if (userInstance1 == NULL)
            {
                userInstance1 = new User(user1);
                users.push_back(userInstance1);
            }
            if (userInstance2 == NULL)
            {
                userInstance2 = new User(user2);
                users.push_back(userInstance2);
            }

            userInstance1->addLink(userInstance2);
            userInstance2->addLink(userInstance1);
        }
        else
        {
            std::cerr << "Parse error in file at line : " << line << std::endl;
            return false;
        }
    }
    return true;
}

int recur(std::list<User *> &cache, const User *first, const User *second)
{
    if (first == second)
        return 0;

    int less = -1;
    for (std::vector<User *>::const_iterator it = first->getLinks().begin(); it != first->getLinks().end(); ++it)
        if (std::find(cache.begin(), cache.end(), *it) == cache.end())
        {
            cache.push_back(*it);
            int tmp = recur(cache, *it, second);
            if (tmp != -1 && (less == -1 || tmp < less))
                less = tmp;
            cache.pop_back();
        }
    return less == -1 ? -1 : ++less;
}

void matrix(std::vector<User *> &users, bool displayMatrix, int max)
{
    std::list<User *> cache;

    int matrix[users.size()][users.size()];
    for (int i = 0; i < users.size(); ++i)
        for (int j = 0; j < users.size(); ++j)
            matrix[i][j] = recur(cache, users[i], users[j]);

    if (!displayMatrix)
        return ;

    for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
        std::cout << (*it)->getName() << std::endl;

    std::cout << std::endl;

    for (int i = 0; i < users.size(); ++i)
    {
        for (int j = 0; j < users.size(); ++j)
        {
            std::cout << (bool)(matrix[i][j] == 1);
            if (j < users.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (int i = 0; i < users.size(); ++i)
    {
        for (int j = 0; j < users.size(); ++j)
        {
            std::cout << (matrix[i][j] > max || matrix[i][j] < 0 ? '0' : (char) (matrix[i][j] + '0'));
            if (j < users.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void links(std::vector<User *> &users, const std::string &user1, const std::string &user2)
{
    User *userInstance1 = NULL;
    User *userInstance2 = NULL;
    for (std::vector<User *>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if ((*it)->getName() == user1)
            userInstance1 = *it;
        if ((*it)->getName() == user2)
            userInstance2 = *it;
    }

    std::list<User *> cache;
    int ret;
    if (userInstance1 == NULL || userInstance2 == NULL)
        ret = -1;
    else
        ret = recur(cache, userInstance1, userInstance2);

    std::cout << "degré de séparation entre " << user1 << " et " << user2 << " : " << ret << std::endl;
}

bool comparator(const User *user1, const User *user2)
{
  return user1->getName() < user2->getName();
}

int main(int ac, char **av)
{
    if (ac != 4 && ac != 3)
    {
        std::cerr << "Usage : " << av[0] << "[number] | [name1 name2]" << std::endl;
        return 84;
    }

    std::vector<User *> users;
    if (!readFile(users, av[1]))
        return 84;

    std::sort(users.begin(), users.end(), comparator);

    if (ac == 3)
    {
        int i = 0;
        while (av[2][i] || i == 0)
        {
            if (av[2][i] < '0' || av[2][i] > '9')
            {
                std::cerr << "Invalid number '" << av[2] << "'" << std::endl;
                return 84;
            }
            ++i;
        }
        matrix(users, true, std::atoi(av[2]));
    }
    else
        links(users, av[2], av[3]);

    return 0;
}
