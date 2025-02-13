#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    // 如果ptr非空 记录r
    if (ptr) ptr->record('r');
    // 创建一个新的resource对象，原本的ptr会被释放，触发其析构函数存入resource
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    // 如果ptr非空在ptr中记录d，然后返回nullptr，释放ptr，触发其析构函数，存入rescords
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    // 如果ptr非空，就在ptr中记录f，然后直接返回ptr，即不释放对象
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr))); // fd
    problems[0] = std::move(RECORDS);// fd

    forward(drop(reset(forward(forward(reset(nullptr)))))); // ffr d
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr)))))); // r d r
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
