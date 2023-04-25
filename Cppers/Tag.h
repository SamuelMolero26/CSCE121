# ifndef _TAG_H
# define _TAG_H

# include <string>
# include <vector>
# include "Post.h"

class Tag {
    private:
        std::string tagName;
        std::vector<Post*> tagPosts;
    
    public:
        Tag(std::string tagName);
        std::string getTagName();
        std::vector<Post*>& getTagPosts();
        void addTagPost(Post* post);
};

# endif
