// impl file system: ls, mkdir -p, cat command
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string join(const vector<string>& input) {
    string output = "";
    bool has_data = false;
    for (size_t i = 0; i < input.size(); ++i) {
        has_data = true;
        output += input[i];
        output += ", ";
    }
    if (has_data) {
        output = output.substr(0, output.length() - 2);
    }
    return output;
}

struct INode {
    string name;    // file name
    string data;    // the date contained in file
    unordered_map<string, INode*> children; // mapping from subdir/file name to inode
    bool isDir;     // default: true
    INode(string str) : name(str), isDir(true) {}
};

// struct FsNode {
//     string name;
//     bool isDir;
//     string content;
//     unordered_map<string, FsNode*> child;

//     FsNode(string str) : name(str), isDir(true) {}
// };

class FileSystem {
    // FsNode m_root;
    INode root; // file system root node
private:   
// given file/dir path, return the corresponding inode
    INode* traverseFileSys(const string& path) {
        INode *resDir = &root;  // result directory
        vector<string> directories = split(path, '/');
        if (directories.empty()) return resDir;

        for (string dir : directories) {
            if (dir.empty()) continue;
            if (!resDir) return NULL;   // invalid path, not existed
            resDir = resDir->children[dir];
        }
        return resDir;
    }

    // FsNode* getFsNode(const string& path) {
    //     FsNode* targetDir = &m_root;

    //     vector<string> dirs = split(path, '/');
    //     for (string dir : dirs) {
    //         if (dir.empty())    continue;

    //         if (targetDir == NULL)  return NULL;
    //         targetDir = targetDir->child[dir];
    //     }

    //     return targetDir;
    // }
public:
    FileSystem() : root("/") {}
    // FileSystem() : m_root("/"), root("/") {}
    vector<string> Ls(const string& path) {
        // IMPLEMENT ME
        vector<string> files;    // result output files
        INode *dir = traverseFileSys(path);
        if (!dir) return files; // empty or not exist

        if (!dir->isDir) {  // is a file
            files.push_back(dir->name);
        }
        else {              // is a dir
            for (auto subDir : dir->children) {
                files.push_back(subDir.first);  // add name
            }
        }
        return files;


        // vector<string> output;

        // FsNode* targetDir = getFsNode(path);
        // if (targetDir) {
        //     if (!targetDir->isDir) output.push_back(targetDir->name);

        //     for (auto ele : targetDir->child) {
        //         output.push_back(ele.first);
        //     }
        // }

        // return output;
    }

    void MkdirP(const string& dir_path) {
        // IMPLEMENT ME

        INode *rootDir = &root, *resDir(NULL);
        vector<string> directories = split(dir_path, '/');
        for (string dir : directories) {
            if (dir.empty()) continue;  // ignore
            resDir = rootDir->children[dir];
            if (!resDir) {  // create non-existed dir
                resDir = new INode(dir);
                rootDir->children[dir] = resDir;
            }
            rootDir = resDir;
        }

    //     FsNode* parent = &m_root;
    //     FsNode* targetDir = NULL;
    //     vector<string> dirs = split(dir_path, '/');
    //     for (string dir : dirs) {
    //         if (dir.empty())    continue;

    //         targetDir = parent->child[dir];
    //         if (targetDir == NULL) {
    //             targetDir = new FsNode(dir);
    //             parent->child[dir] = targetDir;
    //         }

    //         parent = targetDir;
    //     }
    }

    void AddFileWithContent(const string& file_path, const string& content) {
        // IMPLEMENT ME

        MkdirP(file_path);
        INode *file = traverseFileSys(file_path);
        if (file) {
            file->isDir = false;
            file->data = content;    
        }

        // MkdirP(file_path);
        // FsNode* targetDir = getFsNode(file_path);
        // if (targetDir) {
        //     targetDir->isDir = false;
        //     targetDir->content = content;
        // }
    }

    string GetFileContent(const string& file_path) {
        INode *file = traverseFileSys(file_path);
        if (!file || file->isDir) return "";    // not exists, or is a dir
        return file->data;

        // IMPLEMENT ME
        // FsNode* targetDir = getFsNode(file_path);
        // if (targetDir && !targetDir->isDir) {
        //     return targetDir->content;
        // }

        // return "";
    }

// private:
//     FsNode* getFsNode(const string& path) {
//         FsNode* targetDir = &m_root;

//         vector<string> dirs = split(path, '/');
//         for (string dir : dirs) {
//             if (dir.empty())    continue;

//             if (targetDir == NULL)  return NULL;
//             targetDir = targetDir->child[dir];
//         }

//         return targetDir;
//     }
};


#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
    FileSystem fs;

    // should print ""
    cout << join(fs.Ls("/")) << endl;
    assert(join(fs.Ls("/")).empty());

    fs.MkdirP("/a/b/c");
    fs.AddFileWithContent("/a/b/c/d", "hello world");

    // should print a
    cout << join(fs.Ls("/")) << endl;
    assert(join(fs.Ls("/")) == "a");

    // should print d
    cout << join(fs.Ls("/a/b/c")) << endl;
    assert(join(fs.Ls("/a/b/c")) == "d");

    // should print d
    cout << join(fs.Ls("/a/b/c/d")) << endl;
    assert(join(fs.Ls("/a/b/c/d")) == "d");

    // should print hello world
    cout << fs.GetFileContent("/a/b/c/d") << endl;
    assert(fs.GetFileContent("/a/b/c/d") == "hello world");
}

#endif


