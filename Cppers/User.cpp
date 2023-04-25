# include <string>
# include <stdexcept>
#include <vector>
# include "User.h"

using std::string, std::vector;
using namespace std;

User::User(string userName) : userName({userName}), userPosts({vector<Post*>()}){
    // TODO: implement constructor checks
    if(this->userName.empty())
    {
        throw invalid_argument("Empty");
    }


    if(this->userName[0] < 'a'|| this->userName[0] > 'z')
    {
        throw invalid_argument("username starts with lowercase");
    }

    for(char letters : userName)
    {
        if(letters >= 'A' && letters <= 'Z')
        {
            throw invalid_argument("UserName need lowercase");
        }
    }

}

string User::getUserName() {
    // TODO: implement getter
    return userName;
}

vector<Post*>& User::getUserPosts() {
    // TODO: implement getter
    return userPosts;
}

void User::addUserPost(Post* post) {
    // TODO: add post to user posts
    if(post == nullptr)
    {
        throw invalid_argument("Null");
    }
    this->userPosts.push_back(post); 

    
    

}
