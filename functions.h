#include <vector>

void relu(std::vector<std::vector<float>>& vec);
void tanh(std::vector<std::vector<float>>& vec);
void sigmoid(std::vector<float>& v);
void softmax(std::vector<float>& v);
void maxPool(std::vector<std::vector<float>>& v, std::vector<std::vector<float>>& m_pool);
void averagePool(std::vector<std::vector<float>>& v, std::vector<std::vector<float>>& av_pool);
void convolution_npad(std::vector<std::vector<float>>& img, std::vector<std::vector<float>>& kern, std::vector<std::vector<float>>& res);
void convolution_pad(std::vector<std::vector<float>>& img, std::vector<std::vector<float>>& kern, int pad, std::vector<std::vector<float>>& res);
void conv_matrmult_npad(std::vector<std::vector<float>>& img, std::vector<std::vector<float>>& kern, std::vector<std::vector<float>>& res);
void conv_matrmult_pad(std::vector<std::vector<float>>& img, std::vector<std::vector<float>>& kern, int pad, std::vector<std::vector<float>>& res);