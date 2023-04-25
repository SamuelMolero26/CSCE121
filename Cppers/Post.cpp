#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <cctype>
#include <vector>
#include "Post.h"

using std::cout;
using std::string, std::vector, std::stringstream;
using std::invalid_argument;


Post::Post(unsigned int postId, string userName, string postText) : postId(postId), userName(userName), postText(postText) {
    if (postId == 0 || userName == "" || postText == "") {
        throw std::invalid_argument("post constructor: invalid parameter values");
    }
}

unsigned int Post::getPostId() {
    return postId;
}

string Post::getPostUser() {
    return userName;
}

string Post::getPostText() {
    return postText;
}

vector<string> Post::findTags() {
    // TODO: extracts candidate tags based on occurrences of # in the post
   vector<string> tempTags; 

   vector<string> final; // for duplicates

   stringstream read(postText);

   string copyTag;

    bool hasTag = false;
    for(char tag: postText)
    {
        if(tag == '#')
        {
            hasTag = true;
            continue;
        }

        if(hasTag && (isalpha(tag) || tag == '-'))
        {
           copyTag += tolower(tag);
        }

        else if(hasTag && !isalpha(tag) && tag != '-')
        {
            if(ispunct(copyTag.back()))
            {
                copyTag.erase(copyTag.size() - 1);
            }
            tempTags.push_back("#" + copyTag);
            copyTag.clear();
            hasTag = false;
        }
    }

    if(hasTag)
    {
        if(ispunct(copyTag.back()))
        {
            copyTag.erase(copyTag.size() - 1);
        }
        string taga = "#" + copyTag;
        tempTags.push_back(taga);
    }

    //sort and check duplicates

    for (string tag : tempTags)
    {
        bool duplicate = false;
        for(string unique : final)
        {
            if(tag == unique)
            {
                duplicate = true;
                break; 
            }
        }

        if(duplicate == false)
        {
            final.push_back(tag);
        }
    }

    if(final.empty() && tempTags.size() == 1 && tempTags[0] == "#")
    {
        final.push_back("#");
    }

    return final;
   
}
