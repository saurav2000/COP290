#include <vector>

void convolution_layer(std::vector<std::vector<std::vector<float> > > &v1, std::vector<std::vector<std::vector<std::vector<float> > > > &k, std::vector<std::vector<std::vector<float> > > &out);
void maxsampling_layer(std::vector<std::vector<std::vector<float> > > &v1, std::vector<std::vector<std::vector<float> > > &out);
void reluLayer(std::vector<std::vector<std::vector<float> > > &v1);
void bias_add(std::vector<std::vector<std::vector<float> > > &matrix, std::vector<float> &bias);
int readKernel(char* name, std::vector<std::vector<std::vector<std::vector<float> > > > &kern, std::vector<float> &bias, int inputLayers, int outputLayers, int kernelSize);