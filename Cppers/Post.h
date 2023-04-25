# ifndef _POST_H
# define _POST_H

# include <string>
# include <vector>

class Post {
    private:
        unsigned int postId;
        std::string userName;
        std::string postText;
    
    public:
        Post(unsigned int postId, std::string userName, std::string postText);
        unsigned int getPostId();
        std::string getPostUser();
        std::string getPostText();
        std::vector<std::string> findTags();
};

# endif
