#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct layer
{
    std::string nameModel;
    std::vector<std::vector<double>> matrix;
};

class session_an
{

private:
    /* data */
    std::string key;
    std::string id;
    std::vector<layer> models;

public:
    // init
    void init(const std::string &in_key, const std::string &in_id)
    {
        key = in_key;
        id = in_id;
    }

    // add layer
    void addModel(const std::string &modelName, const std::string &initMatrix)
    {
        layer newModel;
        newModel.nameModel = modelName;
        if (initMatrix.empty())
        {
            return;
        }
        std::vector<std::vector<double>> matran;
        std::istringstream iss(initMatrix);
        // get (n,m)
        int n, m;
        iss >> n >> m;

        // n x m
        matran.resize(n, std::vector<double>(m));
        //
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                iss >> matran[i][j];
            }
        }
        newModel.matrix = matran;
        models.push_back(newModel);
    }

    // show
    void showModel()
    {
        std::cout << "Key: " << key << "\n";
        std::cout << "ID: " << id << "\n";
        for (const auto &currentModel : models)
        {
            std::cout << "Model Name: " << currentModel.nameModel << "\n";
            std::cout << "Matrix:\n";

            for (const auto &row : currentModel.matrix)
            {
                for (double element : row)
                {
                    std::cout << element << " ";
                }
                std::cout << "\n";
            }
        }
    }
    std::string get_key(){
        return key;
    }
    std::string get_session_id(){
        return id;
    }
    //
    void cleanModel()
    {
        key = "";
        id = "";
        models.clear();
    }

    //
    layer getModelbyName(const std::string &modelName)
    {
        for (const auto &currentModel : models)
        {
            if (currentModel.nameModel == modelName)
            {
                return currentModel;
            }
        }
        return layer{};
    }
};
