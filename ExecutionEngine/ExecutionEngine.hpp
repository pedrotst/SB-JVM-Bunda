#ifndef EXECUTIONENGINE_HPP
#define EXECUTIONENGINE_HPP
#include<vector>
#include"RuntimeDataArea.hpp"

class Instrucao{

Instrucao();

};

class ExecutionEngine
{
	private:

        vector<Instrucao*> vetorDePonteirosParaFuncao;
        RuntimeDataArea *runtimeDataArea;

	public:
		void SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea);
		void Play(string classComMain);

};

#endif
