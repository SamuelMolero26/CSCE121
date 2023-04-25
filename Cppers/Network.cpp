
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
# include "Network.h"



using std::string, std::vector;
using std::ifstream, std::stringstream;
using namespace std;

Network::Network() : users({}), posts({}), tags({}) {}

void Network::loadFromFile(string fileName) {
    // TODO: load user and post information from file

    ifstream file(fileName);

    if(!file.is_open())
    {
        throw invalid_argument("Can't open file");
    }

    string line;
    vector<string> split_word;
    stringstream ss;

    while(getline(file,line))
    {
        if(line.empty())
        {
            return;
        }

        ss.clear();
        ss << line;
        string word;
        // Split the line into words and add them to the split_word vector
        while(ss >> word)
        {
            split_word.push_back(word);
        }

        // Check the first word of the line to determine the type of entry
        string type = split_word.at(0); 

        if(type == "User")
        {
            try{
                this->addUser(split_word.at(1));
            }catch(const exception& err){
                throw runtime_error("error");
                
            }
        }
        else if(type == "Post")
        {
            size_t sz = split_word.size();
            if(sz < 4){
                throw runtime_error("error");
            }

            unsigned int copy_id = 0;

            try{
                copy_id = (unsigned int)stoi(split_word.at(1));
            }catch(const exception& err)
            {
                throw runtime_error("error");
            }

            string name = split_word.at(2); // grab the name in post
            string post = "";

            for(size_t i = 3; i < sz; i++)
            {
                post += split_word.at(i); 
                if(sz -1 != 1)
                {
                    post += " "; 
                }
            }

            try{
                this->addPost(copy_id,name,post);
            }catch(const exception& err){
                throw runtime_error("error");

            } 
        }
        else{
             throw runtime_error("bad entry");
        }
        split_word.clear();
    }

}

void Network::addUser(string userName) {
    // TODO: create user and add it to network

    for(size_t i = 0; i < userName.size(); i++) // convert everyhtiong to lower case
    {
        userName.at(i) = tolower(userName.at(i)); 
    }


    for(User* tempUser : this->users)
    {
        if(tempUser->getUserName() == userName)
        {
            throw invalid_argument("Username already exists");
        }
    }

    User* User1 = new User(userName);
    this->users.push_back(User1);
    cout << "Added User " << userName << "\n";
    return;

}

void Network::addPost(unsigned int postId, string userName, string postText) {
    // TODO: create post and add it to network
   
    for(Post* tempPost : this->posts)
    {
        if(tempPost->getPostId() == postId)
        {
            throw invalid_argument("Post already in the network");
        }
    }

    //check for the user
    for(size_t i = 0; i < userName.size(); i++) // convert everyhtiong to lower case
    {
        userName.at(i) = tolower(userName.at(i)); 
    }
    
    User* userWanted = nullptr;

    for (User* tempUser : this->users){
          if (tempUser->getUserName() == userName){
            userWanted = tempUser;
            break; 
            
          }
    }
               
    if(!userWanted)
    {
        throw invalid_argument("User is not in network");
    }

    //create the new post
    Post* tempPosts = new Post(postId, userName, postText);
    bool present = false;

    for(string tagsName : tempPosts->findTags())
    {
        present = false; 
        for(Tag * tempTags : this->tags)
        {
            if (tempTags-> getTagName() == tagsName)
            {
                tempTags->addTagPost(tempPosts);
                present = true;
                break;
            }
            
        }
    
        if(present == false)
        {
            try{
                Tag* newTag = new Tag(tagsName);
                newTag->addTagPost(tempPosts);
                this->tags.push_back(newTag);
            }catch(exception& err){
                continue;
            }
        }

    }

    userWanted -> addUserPost(tempPosts);
    this->posts.push_back(tempPosts);
    cout << "Added Post " << to_string(postId) << " by " << userName << endl;
}
    

vector<Post*> Network::getPostsByUser(string userName) {
    // TODO: return posts created by the given user

   if(userName.empty())
   {
        throw invalid_argument("Empty user");
   }

   for(User* tempUser : this->users)
   {
    if(tempUser->getUserName() == userName)
    {
        return tempUser->getUserPosts();
    }
   }

   throw invalid_argument("Not found");

}

vector<Post*> Network::getPostsWithTag(string tagName) {
    // TODO: return posts containing the given tag
    if(tagName.empty())
    {
        throw invalid_argument("Tag is empty");
    }

    for(Tag* tempTag : this->tags)
    {
        if(tempTag ->getTagName() == tagName)
        {
            return tempTag ->getTagPosts();
        }
    }

    throw invalid_argument("Not found");

}

vector<string> Network::getMostPopularHashtag() {
    // TODO: return the tag occurring in most posts

    size_t max = 0; 
    for(Tag* tempTag : this->tags)
    {
        size_t tempMax  = tempTag ->getTagPosts().size();
        if(tempMax > max)
        {
            max = tempMax;
        }

    }

    vector<string> newVect = vector<string>();

   for(Tag* tempTag : this->tags)
   {
        if(tempTag->getTagPosts().size() == max)
        {
            newVect.push_back(tempTag->getTagName());
        }
   }

   return newVect; 
}

Network::~Network() {
    for (unsigned int i = 0; i < users.size(); ++i) {
        delete users.at(i);
    }

    for (unsigned int i = 0; i < tags.size(); ++i) {
        delete tags.at(i);
    }
    
    for (unsigned int i = 0; i < posts.size(); ++i) {
        delete posts.at(i);
    }
}
