# include <string>
# include <stdexcept>
# include "Tag.h"

using std::string, std::vector;
using namespace std; 

Tag::Tag(string tagName): tagName(tagName), tagPosts({}){
    // TODO: implement constructor checks

    if(this->tagName.length() < 2 || this->tagName.at(0) != '#' )
    {
        throw invalid_argument("Error");
    }

    for(char letter: tagName)
    {
        if(letter >= 'A' && letter <= 'Z')
        {
            throw invalid_argument("Need to be lowecase");
        }
    }

    if(this->tagName.at(1) < 'a' || this->tagName.at(1) > 'z')
    {
        throw invalid_argument("second character does not stat with lowercase");
    }

    if(ispunct(this->tagName.back())) // doble check if fail again 
    {
        throw invalid_argument("Error");   
    }
}

string Tag::getTagName() {
    // TODO: implement getter

    return tagName;
}

vector<Post*>& Tag::getTagPosts() {
    // TODO: implement getter

    return tagPosts;
}

void Tag::addTagPost(Post* post) {
    // TODO: add post to tag posts

    if(post == nullptr)
    {
         throw invalid_argument("Null");
    }
    this->tagPosts.push_back(post); 
}
