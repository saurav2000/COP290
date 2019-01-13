#ifndef
#include <vector>
#endif

void relu(std::vector<std::vector<float>> &vec);
void tanh(std::vector<std::vector<float>> &vec);
void sigmoid(std::vector<float> &v);
void softmax(std::vector<float> &v);
std::vector<std::vector<float>>& maxPool(std::vector<std::vector<float>> &v);
std::vector<std::vector<float>>& averagePool(std::vector<std::vector<float>> &v);