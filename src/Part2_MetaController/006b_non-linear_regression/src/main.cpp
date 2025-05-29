#include <vector>
#include <iostream>
#include <random>
#include <torch/torch.h>

/**
 * @brief Generate x,y values on a linear ramp. y = m(x) + b
 *
 * @param b : bias
 * @param m : multiplier
 * @param startX: start of value range
 * @param endX : end of value range
 * @param count : how many x,y pairs to generate
 */
std::vector<std::pair<float, float>> getLine(float b, float m,
                                             float startX, float endX, float count)

{
    float y{0}, dX{0};
    std::vector<std::pair<float, float>> xys;
    dX = (endX - startX) / count; // change in x
    for (float x = startX; x < endX; x += dX)
    {
        y = (m * x) + b;
        xys.push_back({x, y});
    }
    return xys;
}

void printXYs(std::vector<std::pair<float, float>> &xys)
{
    std::cout << "PrintingXYs..." << std::endl;
    for (int i = 0; i < xys.size(); i++)
    {
        std::cout << xys[i] << std::endl;
    }
}

/**
 * @brief
 * @param xys
 * @param low:
 *
 */
void addNoiseToYValues(std::vector<std::pair<float, float>> &xys,
                       float low, float high)
{
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(low, high);
    auto rand = std::bind(distribution, generator);
    for (int i = 0; i < xys.size(); ++i)
    {
        float r = rand();
        // std::cout << "rand: " << r << std::endl;
        xys[i].second += r;
    }
}

int main()
{
    /* 2 x 3 Tensor Example */
    // auto net = torch::nn::Linear(2, 3);
    // for (const auto &p : net->parameters())
    // {
    //     // parameters will be the weight and bias values
    //     std::cout << p << std::endl;
    // }

    // auto input = torch::empty({1, 2}); // initialize a 1 x 2 tensor matrix
    // input[0][0] = 0.5;
    // input[0][1] = 0.25;
    // std::cout << "input" << input << std::endl;
    // auto output = net(input);
    // std::cout << "output:\n"
    //           << output << std::endl;

    /* Full Training Cycle */

    // Generate the Training Data
    std::vector<std::pair<float, float>> xys;
    xys = getLine(5.0, 0.5, 0.0, 10.0, 10.0);
    addNoiseToYValues(xys, -0.1, 0.1);
    printXYs(xys);

    auto net = torch::nn::Linear(1, 1);
    for (auto p : net->parameters())
    {
        std::cout << "parameter: " << p << std::endl;
    }

    // Assign X values to the Input Tensor
    torch::Tensor in_t = torch::empty({(long)xys.size(), 1});
    for (int i = 0; i < xys.size(); ++i)
    {
        in_t[i][0] = xys[i].first; // first is x
    }

    // Print resulting Y value guesses
    torch::Tensor out_t = net(in_t);
    std::cout << "output: " << out_t << std::endl;

    // Set up Training Tensor with correct values
    torch::Tensor correct_t = torch::empty({(long)xys.size(), 1});

    for (int i = 0; i < xys.size(); ++i)
    {
        correct_t[i][0] = xys[i].second; // second is y
    }

    // Train the Network
    torch::optim::SGD optimizer(net->parameters(), 0.01);
    float loss = 1000;
    while (loss > 0.5)
    {
        // Calculate current loss
        torch::Tensor loss_t = torch::mse_loss(net(in_t), correct_t); // net(in_t) computes new predictions with the current updated weights
        loss = loss_t.item<float>();
        std::cout << "loss (training): " << loss << std::endl;

        // Optimize
        optimizer.zero_grad(); // reset the optimizer
        loss_t.backward();     // compute changes required to network parameters
        optimizer.step();      // update network parameters
    }
}