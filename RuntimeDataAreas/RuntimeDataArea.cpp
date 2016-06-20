Frame::Frame()
{
	
}

DadosDaClasse *RuntimeDataArea::CarregarClasse(const string &nomeDaClasse)
{
	string nomeSemExtensao= nomeDaClasse;
	if(StringUtilidadesTerminaCom(nomeClasse, ".class")
	{
		nomeSemExtensao= RemoverNoFinal(nomeSemExtensao, ".class");
	}
	if(classes.count(nomeSemExtensao) >0)
	{
		return classes[nomeSemExtensao];
	}
	string nomeComExtensao= nomeDaClasse;
	if (!StringUtilidades::TerminaCom(nomeComExtensao, ".class")
	{
		nomeComExtensao+= ".class";
	}
	classes[nomeSemExtensao] = classLoader->CarregarClasse(nomeComExtensao);

	// adicionando <clinit> da classe (se existir) na stack frame.

	if(MetodoExiste(nomeSemExtensao, "<clinit>", "()V"))
	{
		//pseudocodigo:
		Frame *novoFrame= new Frame(classes[nomeSemExtensao], "<clinit>", "()V");
		EmpilharFrame(novoFrame);

}

void RuntimeDataArea::SetClassLoader(ClassLoader *classLoader)
{
	this.classLoader =classLoader;
}

void RuntimeDataArea::SetExecutionEngine(ExecutionEngine *executionEngine)
{
	this.executionEngine =executionEngine;
}
