#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Comment {
    string id;
    string postId;
    string userId;
    string parentId;
    string description;
    vector<Comment> comments;
    string getUniqueId();
public:
    Comment(string);
    void setPostId(string);
    void setUserId(string);
    void setDescription(string);
    void setParentId(string);
    string getId();
    string getUserId();
    void addToComments(Comment& comment);
    bool editNestedComment(string, string);  // commentId, desc
    bool deleteNestedComment(string);  // commentId
};

class Post {
    string id;
    vector<Comment> comments;
    string getUniqueId();
public:
    Post();
    string getId();
    const vector<Comment>& getComments() const;
    void addToComments(Comment&);
    void addNestedComment(string, Comment&);
    bool editComment(string, string, string);
    bool deleteComment(string, string);
};

class User {
    string id;
    string name;
    string getUniqueId();
public:
    User(string);
    string getId();
    void addCommentToPost(Post&, Comment&);
    void replyToComment(Post&, string, Comment&);
    bool editComment(Post&, string, string, string);
    bool deleteComment(Post&, string, string);
};

string Comment::getUniqueId(){
    static int commentId = 1;
    return "c" + to_string(commentId++);
}

Comment::Comment(string desc){
    this->id = getUniqueId();
    this->description = desc;
}

void Comment::setDescription(string desc){
    this->description = desc;
}

void Comment::setPostId(string postId){
    this->postId = postId;
}

void Comment::setUserId(string userId){
    this->userId = userId;
}

void Comment::setParentId(string parentId){
    this->parentId = parentId;
}

string Comment::getId(){
    return this->id;
}

string Comment::getUserId() {
    return this->userId;
}

void Comment::addToComments(Comment& comment){
    comments.push_back(comment);
}

bool Comment::editNestedComment(string commentId, string desc){
    for(Comment& comment : comments){
        if(comment.getId() == commentId){
            comment.setDescription(desc);
            return true;
        }
    }
    return false;
}

bool Comment::deleteNestedComment(string commentId){
    int i = 0;
    for(Comment& comment : comments){
        if(comment.getId() == commentId){
            comments.erase(comments.begin()+i);
            return true;
        }
        ++i;
    }
    return false;
}

string Post::getUniqueId(){
    static int postId = 1;
    return "p" + to_string(postId++);
}

Post::Post(){
    this->id = getUniqueId();
}

string Post::getId(){
    return this->id;
}

const vector<Comment>& Post::getComments() const {
    return this->comments;
}

void Post::addToComments(Comment& comment){
    comments.push_back(comment);
}

void Post::addNestedComment(string parentId, Comment& comment){
    for(Comment& comm : comments){
        if(comm.getId() == parentId){
            comm.addToComments(comment);
        }
    }
}

bool Post::editComment(string parentId, string commentId, string desc){

    for(Comment& comment : comments){
        if(comment.getId() == parentId){
            if(parentId == commentId){
                comment.setDescription(desc);
                return true;
            }
            else{
                return comment.editNestedComment(commentId, desc);
            }
        }
    }
    return false;
}

bool Post::deleteComment(string parentId, string commentId){
    int i = 0;
    for(Comment& comment : comments){
        if(comment.getId() == parentId){
            if(parentId == commentId){
                comments.erase(comments.begin()+i);
                return true;
            }
            else{
                return comment.deleteNestedComment(commentId);
            }
        }
        ++i;
    }
    return false;
}

string User::getUniqueId(){
    static int userId = 1;
    return "u" + to_string(userId++);
}

User::User(string name){
    this->id = getUniqueId();
    this->name = name;
}

void User::addCommentToPost(Post& post, Comment& comment){
    comment.setUserId(this->id);
    comment.setPostId(post.getId());
    comment.setParentId(comment.getId());
    post.addToComments(comment);
}

void User::replyToComment(Post& post, string parentId, Comment& comment){
    comment.setUserId(this->id);
    comment.setPostId(post.getId());
    comment.setParentId(parentId);
    post.addNestedComment(parentId, comment);
}

bool User::editComment(Post& post, string parentId, string commentId, string desc){
    for(Comment comment : post.getComments()){
        if(comment.getId() == commentId){
            if(comment.getUserId() != this->id){
                cout<<"Unauthorized to edit the comment!\n";
                return false;
            }
            break;
        }
    }
    return post.editComment(parentId, commentId, desc);
}

bool User::deleteComment(Post& post, string parentId, string commentId){
    for(Comment comment : post.getComments()){
        if(comment.getId() == commentId){
            if(comment.getUserId() != this->id){
                cout<<"Unauthorized to delete the comment!\n";
                return false;
            }
            break;
        }
    }
    return post.deleteComment(parentId, commentId);
}

int main() {
    cout<<"Facebook Comment!\n";
    return 0;
}