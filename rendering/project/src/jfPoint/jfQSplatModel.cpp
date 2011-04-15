#include "jfQSplatModel.hpp"

jfQSplatModel::jfQSplatModel(string filename)
{
	m_Model = QSplat_Model::Open(filename.c_str());
}

jfQSplatModel::~jfQSplatModel()
{
}
