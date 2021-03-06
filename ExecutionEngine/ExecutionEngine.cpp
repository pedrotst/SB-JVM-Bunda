#include "ExecutionEngine.hpp"

ExecutionEngine::ExecutionEngine(void)
{

}

void ExecutionEngine::SetRuntimeDataArea(RuntimeDataArea *runtimeDataArea)
{
	this->runtimeDataArea= runtimeDataArea;
}

void ExecutionEngine::Play(string classComMain)
{


	uint8_t instrucao;
	Objeto *obj = new Objeto();

	obj->javaClass = runtimeDataArea->CarregarClasse(classComMain);
	obj->instancia = NULL;

	runtimeDataArea->empilharFrame(new Frame(obj, "main", "([Ljava/lang/String;)V"));

	if(obj->javaClass->getMetodo("<clinit>","()V") != NULL){

		runtimeDataArea->empilharFrame(new Frame(obj, "<clinit>","()V"));
	}

	do
	{

		instrucao = *(runtimeDataArea->topoPilha()->getCode());
		(this->*vetorDePonteirosParaFuncao[instrucao])();

	}
	while(runtimeDataArea->pilhaJVM.size() > 0);
}

void ExecutionEngine::inicializaInstrucoes() {

	vetorDePonteirosParaFuncao[0x00] = &ExecutionEngine::i_nop;
	vetorDePonteirosParaFuncao[0x01] = &ExecutionEngine::i_aconst_null;
	vetorDePonteirosParaFuncao[0x02] = &ExecutionEngine::i_iconst_m1;
	vetorDePonteirosParaFuncao[0x03] = &ExecutionEngine::i_iconst_0;
	vetorDePonteirosParaFuncao[0x04] = &ExecutionEngine::i_iconst_1;
	vetorDePonteirosParaFuncao[0x05] = &ExecutionEngine::i_iconst_2;
	vetorDePonteirosParaFuncao[0x06] = &ExecutionEngine::i_iconst_3;
	vetorDePonteirosParaFuncao[0x07] = &ExecutionEngine::i_iconst_4;
	vetorDePonteirosParaFuncao[0x08] = &ExecutionEngine::i_iconst_5;
	vetorDePonteirosParaFuncao[0x09] = &ExecutionEngine::i_lconst_0;
	vetorDePonteirosParaFuncao[0x0a] = &ExecutionEngine::i_lconst_1;
	vetorDePonteirosParaFuncao[0x0b] = &ExecutionEngine::i_fconst_0;
	vetorDePonteirosParaFuncao[0x0c] = &ExecutionEngine::i_fconst_1;
	vetorDePonteirosParaFuncao[0x0d] = &ExecutionEngine::i_fconst_2;
	vetorDePonteirosParaFuncao[0x0e] = &ExecutionEngine::i_dconst_0;
	vetorDePonteirosParaFuncao[0x0f] = &ExecutionEngine::i_dconst_1;
	vetorDePonteirosParaFuncao[0x10] = &ExecutionEngine::i_bipush;
	vetorDePonteirosParaFuncao[0x11] = &ExecutionEngine::i_sipush;
	vetorDePonteirosParaFuncao[0x12] = &ExecutionEngine::i_ldc;
	vetorDePonteirosParaFuncao[0x13] = &ExecutionEngine::i_ldc_w;
	vetorDePonteirosParaFuncao[0x14] = &ExecutionEngine::i_ldc2_w;
	vetorDePonteirosParaFuncao[0x15] = &ExecutionEngine::i_iload;
	vetorDePonteirosParaFuncao[0x16] = &ExecutionEngine::i_lload;
	vetorDePonteirosParaFuncao[0x17] = &ExecutionEngine::i_fload;
	vetorDePonteirosParaFuncao[0x18] = &ExecutionEngine::i_dload;
	vetorDePonteirosParaFuncao[0x19] = &ExecutionEngine::i_aload;
	vetorDePonteirosParaFuncao[0x1a] = &ExecutionEngine::i_iload_0;
	vetorDePonteirosParaFuncao[0x1b] = &ExecutionEngine::i_iload_1;
	vetorDePonteirosParaFuncao[0x1c] = &ExecutionEngine::i_iload_2;
	vetorDePonteirosParaFuncao[0x1d] = &ExecutionEngine::i_iload_3;
	vetorDePonteirosParaFuncao[0x1e] = &ExecutionEngine::i_lload_0;
	vetorDePonteirosParaFuncao[0x1f] = &ExecutionEngine::i_lload_1;
	vetorDePonteirosParaFuncao[0x20] = &ExecutionEngine::i_lload_2;
	vetorDePonteirosParaFuncao[0x21] = &ExecutionEngine::i_lload_3;
	vetorDePonteirosParaFuncao[0x22] = &ExecutionEngine::i_fload_0;
	vetorDePonteirosParaFuncao[0x23] = &ExecutionEngine::i_fload_1;
	vetorDePonteirosParaFuncao[0x24] = &ExecutionEngine::i_fload_2;
	vetorDePonteirosParaFuncao[0x25] = &ExecutionEngine::i_fload_3;
	vetorDePonteirosParaFuncao[0x26] = &ExecutionEngine::i_dload_0;
	vetorDePonteirosParaFuncao[0x27] = &ExecutionEngine::i_dload_1;
	vetorDePonteirosParaFuncao[0x28] = &ExecutionEngine::i_dload_2;
	vetorDePonteirosParaFuncao[0x29] = &ExecutionEngine::i_dload_3;
	vetorDePonteirosParaFuncao[0x2a] = &ExecutionEngine::i_aload_0;
	vetorDePonteirosParaFuncao[0x2b] = &ExecutionEngine::i_aload_1;
	vetorDePonteirosParaFuncao[0x2c] = &ExecutionEngine::i_aload_2;
	vetorDePonteirosParaFuncao[0x2d] = &ExecutionEngine::i_aload_3;
	vetorDePonteirosParaFuncao[0x2e] = &ExecutionEngine::i_iaload;
	vetorDePonteirosParaFuncao[0x2f] = &ExecutionEngine::i_laload;
	vetorDePonteirosParaFuncao[0x30] = &ExecutionEngine::i_faload;
	vetorDePonteirosParaFuncao[0x31] = &ExecutionEngine::i_daload;
	vetorDePonteirosParaFuncao[0x32] = &ExecutionEngine::i_aaload;
	vetorDePonteirosParaFuncao[0x33] = &ExecutionEngine::i_baload;
	vetorDePonteirosParaFuncao[0x34] = &ExecutionEngine::i_caload;
	vetorDePonteirosParaFuncao[0x35] = &ExecutionEngine::i_saload;
	vetorDePonteirosParaFuncao[0x36] = &ExecutionEngine::i_istore;
	vetorDePonteirosParaFuncao[0x37] = &ExecutionEngine::i_lstore;
	vetorDePonteirosParaFuncao[0x38] = &ExecutionEngine::i_fstore;
	vetorDePonteirosParaFuncao[0x39] = &ExecutionEngine::i_dstore;
	vetorDePonteirosParaFuncao[0x3a] = &ExecutionEngine::i_astore;
	vetorDePonteirosParaFuncao[0x3b] = &ExecutionEngine::i_istore_0;
	vetorDePonteirosParaFuncao[0x3c] = &ExecutionEngine::i_istore_1;
	vetorDePonteirosParaFuncao[0x3d] = &ExecutionEngine::i_istore_2;
	vetorDePonteirosParaFuncao[0x3e] = &ExecutionEngine::i_istore_3;
	vetorDePonteirosParaFuncao[0x3f] = &ExecutionEngine::i_lstore_0;
	vetorDePonteirosParaFuncao[0x40] = &ExecutionEngine::i_lstore_1;
	vetorDePonteirosParaFuncao[0x41] = &ExecutionEngine::i_lstore_2;
	vetorDePonteirosParaFuncao[0x42] = &ExecutionEngine::i_lstore_3;
	vetorDePonteirosParaFuncao[0x43] = &ExecutionEngine::i_fstore_0;
	vetorDePonteirosParaFuncao[0x44] = &ExecutionEngine::i_fstore_1;
	vetorDePonteirosParaFuncao[0x45] = &ExecutionEngine::i_fstore_2;
	vetorDePonteirosParaFuncao[0x46] = &ExecutionEngine::i_fstore_3;
	vetorDePonteirosParaFuncao[0x47] = &ExecutionEngine::i_dstore_0;
	vetorDePonteirosParaFuncao[0x48] = &ExecutionEngine::i_dstore_1;
	vetorDePonteirosParaFuncao[0x49] = &ExecutionEngine::i_dstore_2;
	vetorDePonteirosParaFuncao[0x4a] = &ExecutionEngine::i_dstore_3;
	vetorDePonteirosParaFuncao[0x4b] = &ExecutionEngine::i_astore_0;
	vetorDePonteirosParaFuncao[0x4c] = &ExecutionEngine::i_astore_1;
	vetorDePonteirosParaFuncao[0x4d] = &ExecutionEngine::i_astore_2;
	vetorDePonteirosParaFuncao[0x4e] = &ExecutionEngine::i_astore_3;
	vetorDePonteirosParaFuncao[0x4f] = &ExecutionEngine::i_iastore;
	vetorDePonteirosParaFuncao[0x50] = &ExecutionEngine::i_lastore;
	vetorDePonteirosParaFuncao[0x51] = &ExecutionEngine::i_fastore;
	vetorDePonteirosParaFuncao[0x52] = &ExecutionEngine::i_dastore;
	vetorDePonteirosParaFuncao[0x53] = &ExecutionEngine::i_aastore;
	vetorDePonteirosParaFuncao[0x54] = &ExecutionEngine::i_bastore;
	vetorDePonteirosParaFuncao[0x55] = &ExecutionEngine::i_castore;
	vetorDePonteirosParaFuncao[0x56] = &ExecutionEngine::i_sastore;
	vetorDePonteirosParaFuncao[0x57] = &ExecutionEngine::i_pop;
	vetorDePonteirosParaFuncao[0x58] = &ExecutionEngine::i_pop2;
	vetorDePonteirosParaFuncao[0x59] = &ExecutionEngine::i_dup;
	vetorDePonteirosParaFuncao[0x5a] = &ExecutionEngine::i_dup2_x1;
	vetorDePonteirosParaFuncao[0x5b] = &ExecutionEngine::i_dup2_x2;
	vetorDePonteirosParaFuncao[0x5c] = &ExecutionEngine::i_dup2;
	vetorDePonteirosParaFuncao[0x5d] = &ExecutionEngine::i_dup2_x1;
	vetorDePonteirosParaFuncao[0x5e] = &ExecutionEngine::i_dup2_x2;
	vetorDePonteirosParaFuncao[0x5f] = &ExecutionEngine::i_swap;
	vetorDePonteirosParaFuncao[0x60] = &ExecutionEngine::i_iadd;
	vetorDePonteirosParaFuncao[0x61] = &ExecutionEngine::i_ladd;
	vetorDePonteirosParaFuncao[0x62] = &ExecutionEngine::i_fadd;
	vetorDePonteirosParaFuncao[0x63] = &ExecutionEngine::i_dadd;
	vetorDePonteirosParaFuncao[0x64] = &ExecutionEngine::i_isub;
	vetorDePonteirosParaFuncao[0x65] = &ExecutionEngine::i_lsub;
	vetorDePonteirosParaFuncao[0x66] = &ExecutionEngine::i_fsub;
	vetorDePonteirosParaFuncao[0x67] = &ExecutionEngine::i_dsub;
	vetorDePonteirosParaFuncao[0x68] = &ExecutionEngine::i_imul;
	vetorDePonteirosParaFuncao[0x69] = &ExecutionEngine::i_lmul;
	vetorDePonteirosParaFuncao[0x6a] = &ExecutionEngine::i_fmul;
	vetorDePonteirosParaFuncao[0x6b] = &ExecutionEngine::i_dmul;
	vetorDePonteirosParaFuncao[0x6c] = &ExecutionEngine::i_idiv;
	vetorDePonteirosParaFuncao[0x6d] = &ExecutionEngine::i_ldiv;
	vetorDePonteirosParaFuncao[0x6e] = &ExecutionEngine::i_fdiv;
	vetorDePonteirosParaFuncao[0x6f] = &ExecutionEngine::i_ddiv;
	vetorDePonteirosParaFuncao[0x70] = &ExecutionEngine::i_irem;
	vetorDePonteirosParaFuncao[0x71] = &ExecutionEngine::i_lrem;
	vetorDePonteirosParaFuncao[0x72] = &ExecutionEngine::i_frem;
	vetorDePonteirosParaFuncao[0x73] = &ExecutionEngine::i_drem;
	vetorDePonteirosParaFuncao[0x74] = &ExecutionEngine::i_ineg;
	vetorDePonteirosParaFuncao[0x75] = &ExecutionEngine::i_lneg;
	vetorDePonteirosParaFuncao[0x76] = &ExecutionEngine::i_fneg;
	vetorDePonteirosParaFuncao[0x77] = &ExecutionEngine::i_dneg;
	vetorDePonteirosParaFuncao[0x78] = &ExecutionEngine::i_ishl;
	vetorDePonteirosParaFuncao[0x79] = &ExecutionEngine::i_lshl;
	vetorDePonteirosParaFuncao[0x7a] = &ExecutionEngine::i_ishr;
	vetorDePonteirosParaFuncao[0x7b] = &ExecutionEngine::i_lshr;
	vetorDePonteirosParaFuncao[0x7c] = &ExecutionEngine::i_iushr;
	vetorDePonteirosParaFuncao[0x7d] = &ExecutionEngine::i_lushr;
	vetorDePonteirosParaFuncao[0x7e] = &ExecutionEngine::i_iand;
	vetorDePonteirosParaFuncao[0x7f] = &ExecutionEngine::i_land;
	vetorDePonteirosParaFuncao[0x80] = &ExecutionEngine::i_ior;
	vetorDePonteirosParaFuncao[0x81] = &ExecutionEngine::i_lor;
	vetorDePonteirosParaFuncao[0x82] = &ExecutionEngine::i_ixor;
	vetorDePonteirosParaFuncao[0x83] = &ExecutionEngine::i_lxor;
	vetorDePonteirosParaFuncao[0x84] = &ExecutionEngine::i_iinc;
	vetorDePonteirosParaFuncao[0x85] = &ExecutionEngine::i_i2l;
	vetorDePonteirosParaFuncao[0x86] = &ExecutionEngine::i_i2f;
	vetorDePonteirosParaFuncao[0x87] = &ExecutionEngine::i_i2d;
	vetorDePonteirosParaFuncao[0x88] = &ExecutionEngine::i_l2i;
	vetorDePonteirosParaFuncao[0x89] = &ExecutionEngine::i_l2f;
	vetorDePonteirosParaFuncao[0x8a] = &ExecutionEngine::i_l2d;
	vetorDePonteirosParaFuncao[0x8b] = &ExecutionEngine::i_f2i;
	vetorDePonteirosParaFuncao[0x8c] = &ExecutionEngine::i_f2l;
	vetorDePonteirosParaFuncao[0x8d] = &ExecutionEngine::i_f2d;
	vetorDePonteirosParaFuncao[0x8e] = &ExecutionEngine::i_d2i;
	vetorDePonteirosParaFuncao[0x8f] = &ExecutionEngine::i_d2l;
	vetorDePonteirosParaFuncao[0x90] = &ExecutionEngine::i_d2f;
	vetorDePonteirosParaFuncao[0x91] = &ExecutionEngine::i_i2b;
	vetorDePonteirosParaFuncao[0x92] = &ExecutionEngine::i_i2c;
	vetorDePonteirosParaFuncao[0x93] = &ExecutionEngine::i_i2s;
	vetorDePonteirosParaFuncao[0x94] = &ExecutionEngine::i_lcmp;
	vetorDePonteirosParaFuncao[0x95] = &ExecutionEngine::i_fcmpl;
	vetorDePonteirosParaFuncao[0x96] = &ExecutionEngine::i_fcmpg;
	vetorDePonteirosParaFuncao[0x97] = &ExecutionEngine::i_dcmpl;
	vetorDePonteirosParaFuncao[0x98] = &ExecutionEngine::i_dcmpg;
	vetorDePonteirosParaFuncao[0x99] = &ExecutionEngine::i_ifeq;
	vetorDePonteirosParaFuncao[0x9a] = &ExecutionEngine::i_ifne;
	vetorDePonteirosParaFuncao[0x9b] = &ExecutionEngine::i_iflt;
	vetorDePonteirosParaFuncao[0x9c] = &ExecutionEngine::i_ifge;
	vetorDePonteirosParaFuncao[0x9d] = &ExecutionEngine::i_ifgt;
	vetorDePonteirosParaFuncao[0x9e] = &ExecutionEngine::i_ifle;
	vetorDePonteirosParaFuncao[0x9f] = &ExecutionEngine::i_if_icmpeq;
	vetorDePonteirosParaFuncao[0xa0] = &ExecutionEngine::i_if_icmpne;
	vetorDePonteirosParaFuncao[0xa1] = &ExecutionEngine::i_if_icmplt;
	vetorDePonteirosParaFuncao[0xa2] = &ExecutionEngine::i_if_icmpge;
	vetorDePonteirosParaFuncao[0xa3] = &ExecutionEngine::i_if_icmpgt;
	vetorDePonteirosParaFuncao[0xa4] = &ExecutionEngine::i_if_icmple;
	vetorDePonteirosParaFuncao[0xa5] = &ExecutionEngine::i_if_acmpeq;
	vetorDePonteirosParaFuncao[0xa6] = &ExecutionEngine::i_if_acmpne;
	vetorDePonteirosParaFuncao[0xa7] = &ExecutionEngine::i_goto;
	vetorDePonteirosParaFuncao[0xa8] = &ExecutionEngine::i_jsr;
	vetorDePonteirosParaFuncao[0xa9] = &ExecutionEngine::i_ret;
	vetorDePonteirosParaFuncao[0xaa] = &ExecutionEngine::i_tableswitch;
	vetorDePonteirosParaFuncao[0xab] = &ExecutionEngine::i_lookupswitch;
	vetorDePonteirosParaFuncao[0xac] = &ExecutionEngine::i_ireturn;
	vetorDePonteirosParaFuncao[0xad] = &ExecutionEngine::i_lreturn;
	vetorDePonteirosParaFuncao[0xae] = &ExecutionEngine::i_freturn;
	vetorDePonteirosParaFuncao[0xaf] = &ExecutionEngine::i_dreturn;
	vetorDePonteirosParaFuncao[0xb0] = &ExecutionEngine::i_areturn;
	vetorDePonteirosParaFuncao[0xb1] = &ExecutionEngine::i_return;
	vetorDePonteirosParaFuncao[0xb2] = &ExecutionEngine::i_getstatic;
	vetorDePonteirosParaFuncao[0xb3] = &ExecutionEngine::i_putstatic;
	vetorDePonteirosParaFuncao[0xb4] = &ExecutionEngine::i_getfield;
	vetorDePonteirosParaFuncao[0xb5] = &ExecutionEngine::i_putfield;
	vetorDePonteirosParaFuncao[0xb6] = &ExecutionEngine::i_invokevirtual;
	vetorDePonteirosParaFuncao[0xb7] = &ExecutionEngine::i_invokespecial;
	vetorDePonteirosParaFuncao[0xb8] = &ExecutionEngine::i_invokestatic;
	vetorDePonteirosParaFuncao[0xb9] = &ExecutionEngine::i_invokeinterface;
	vetorDePonteirosParaFuncao[0xbb] = &ExecutionEngine::i_new;
	vetorDePonteirosParaFuncao[0xbc] = &ExecutionEngine::i_newarray;
	vetorDePonteirosParaFuncao[0xbd] = &ExecutionEngine::i_anewarray;
	vetorDePonteirosParaFuncao[0xbe] = &ExecutionEngine::i_arraylength;
	vetorDePonteirosParaFuncao[0xbf] = &ExecutionEngine::i_athrow;
	vetorDePonteirosParaFuncao[0xc0] = &ExecutionEngine::i_checkcast;
	vetorDePonteirosParaFuncao[0xc1] = &ExecutionEngine::i_instanceof;
	vetorDePonteirosParaFuncao[0xc2] = &ExecutionEngine::i_monitorenter;
	vetorDePonteirosParaFuncao[0xc3] = &ExecutionEngine::i_monitorexit;
	vetorDePonteirosParaFuncao[0xc4] = &ExecutionEngine::i_wide;
	vetorDePonteirosParaFuncao[0xc5] = &ExecutionEngine::i_multianewarray;
	vetorDePonteirosParaFuncao[0xc6] = &ExecutionEngine::i_ifnull;
	vetorDePonteirosParaFuncao[0xc7] = &ExecutionEngine::i_ifnonnull;
	vetorDePonteirosParaFuncao[0xc8] = &ExecutionEngine::i_goto_w;
	vetorDePonteirosParaFuncao[0xc9] = &ExecutionEngine::i_jsr_w;

}

void ExecutionEngine::i_nop(){
	//anda uma posição e faz nada
	//incrementa pc + 1
	runtimeDataArea->topoPilha()->incrementaPC(1);

}

void ExecutionEngine::i_aconst_null(){
	Frame *toppilha = runtimeDataArea->topoPilha();
	Valor valor;
	valor.tipo = TipoDado::REFERENCE;
	valor.dado = (uint32_t)NULL;
	toppilha->empilharOperando(valor);
}

void ExecutionEngine::i_iconst_m1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)-1;
	//falta uma parada de print do bastos

	toppilha->empilharOperando(valor);

	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_0(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)0;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_1(){

	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)1;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_iconst_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)2;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_3(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)3;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_iconst_4(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)4;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);

}
void ExecutionEngine::i_iconst_5(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::INT;
	valor.dado = (uint32_t)5;
	//falta uma parada de print do bastos
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_lconst_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor padding;
	padding.tipo = TipoDado::HIGHLONG;
	padding.dado = (uint32_t)0;

	Valor valor;
	valor.tipo = TipoDado::LOWLONG;
	valor.dado = (uint32_t)0;

	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);


}
void ExecutionEngine::i_lconst_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor padding;
	padding.tipo = TipoDado::HIGHLONG;
	padding.dado = (uint32_t)0;

	Valor valor;
	valor.tipo = TipoDado::LOWLONG;
	valor.dado = (uint32_t)1;

	toppilha->empilharOperando(padding);
	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_0(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)0;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_1(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)1;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_fconst_2(){
	Frame *toppilha = runtimeDataArea->topoPilha();

	Valor valor;
	valor.tipo = TipoDado::FLOAT;
	valor.dado = (uint32_t)2;

	toppilha->empilharOperando(valor);
	runtimeDataArea->topoPilha()->incrementaPC(1);
}
void ExecutionEngine::i_dconst_0(){




}
void ExecutionEngine::i_dconst_1(){}
void ExecutionEngine::i_bipush(){}
void ExecutionEngine::i_sipush(){}
void ExecutionEngine::i_ldc(){}
void ExecutionEngine::i_ldc_w(){}
void ExecutionEngine::i_ldc2_w(){}
void ExecutionEngine::i_iload(){}
void ExecutionEngine::i_lload(){}
void ExecutionEngine::i_fload(){}
void ExecutionEngine::i_dload(){}
void ExecutionEngine::i_aload(){}
void ExecutionEngine::i_iload_0(){}
void ExecutionEngine::i_iload_1(){}
void ExecutionEngine::i_iload_2(){}
void ExecutionEngine::i_iload_3(){}
void ExecutionEngine::i_lload_0(){}
void ExecutionEngine::i_lload_1(){}
void ExecutionEngine::i_lload_2(){}
void ExecutionEngine::i_lload_3(){}
void ExecutionEngine::i_fload_0(){}
void ExecutionEngine::i_fload_1(){}
void ExecutionEngine::i_fload_2(){}
void ExecutionEngine::i_fload_3(){}
void ExecutionEngine::i_dload_0(){}
void ExecutionEngine::i_dload_1(){}
void ExecutionEngine::i_dload_2(){}
void ExecutionEngine::i_dload_3(){}
void ExecutionEngine::i_aload_0(){}
void ExecutionEngine::i_aload_1(){}
void ExecutionEngine::i_aload_2(){}
void ExecutionEngine::i_aload_3(){}
void ExecutionEngine::i_iaload(){}
void ExecutionEngine::i_laload(){}
void ExecutionEngine::i_faload(){}
void ExecutionEngine::i_daload(){}
void ExecutionEngine::i_aaload(){}
void ExecutionEngine::i_baload(){}
void ExecutionEngine::i_caload(){}
void ExecutionEngine::i_saload(){}
void ExecutionEngine::i_istore(){}
void ExecutionEngine::i_lstore(){}
void ExecutionEngine::i_fstore(){}
void ExecutionEngine::i_dstore(){}
void ExecutionEngine::i_astore(){}
void ExecutionEngine::i_istore_0(){}
void ExecutionEngine::i_istore_1(){}
void ExecutionEngine::i_istore_2(){}
void ExecutionEngine::i_istore_3(){}
void ExecutionEngine::i_lstore_0(){}
void ExecutionEngine::i_lstore_1(){}
void ExecutionEngine::i_lstore_2(){}
void ExecutionEngine::i_lstore_3(){}
void ExecutionEngine::i_fstore_0(){}
void ExecutionEngine::i_fstore_1(){}
void ExecutionEngine::i_fstore_2(){}
void ExecutionEngine::i_fstore_3(){}
void ExecutionEngine::i_dstore_0(){}
void ExecutionEngine::i_dstore_1(){}
void ExecutionEngine::i_dstore_2(){}
void ExecutionEngine::i_dstore_3(){}
void ExecutionEngine::i_astore_0(){}
void ExecutionEngine::i_astore_1(){}
void ExecutionEngine::i_astore_2(){}
void ExecutionEngine::i_astore_3(){}
void ExecutionEngine::i_iastore(){}
void ExecutionEngine::i_lastore(){}
void ExecutionEngine::i_fastore(){}
void ExecutionEngine::i_dastore(){}
void ExecutionEngine::i_aastore(){}
void ExecutionEngine::i_bastore(){}
void ExecutionEngine::i_castore(){}
void ExecutionEngine::i_sastore(){}
void ExecutionEngine::i_pop(){}
void ExecutionEngine::i_pop2(){}
void ExecutionEngine::i_dup(){}
void ExecutionEngine::i_dup_x1(){}
void ExecutionEngine::i_dup_x2(){}
void ExecutionEngine::i_dup2(){}
void ExecutionEngine::i_dup2_x1(){}
void ExecutionEngine::i_dup2_x2(){}
void ExecutionEngine::i_swap(){}
void ExecutionEngine::i_iadd(){}
void ExecutionEngine::i_ladd(){}
void ExecutionEngine::i_fadd(){}
void ExecutionEngine::i_dadd(){}
void ExecutionEngine::i_isub(){}
void ExecutionEngine::i_lsub(){}
void ExecutionEngine::i_fsub(){}
void ExecutionEngine::i_dsub(){}
void ExecutionEngine::i_imul(){}
void ExecutionEngine::i_lmul(){}
void ExecutionEngine::i_fmul(){}
void ExecutionEngine::i_dmul(){}
void ExecutionEngine::i_idiv(){}
void ExecutionEngine::i_ldiv(){}
void ExecutionEngine::i_fdiv(){}
void ExecutionEngine::i_ddiv(){}
void ExecutionEngine::i_irem(){}
void ExecutionEngine::i_lrem(){}
void ExecutionEngine::i_frem(){}
void ExecutionEngine::i_drem(){}
void ExecutionEngine::i_ineg(){}
void ExecutionEngine::i_lneg(){}
void ExecutionEngine::i_fneg(){}
void ExecutionEngine::i_dneg(){}
void ExecutionEngine::i_ishl(){}
void ExecutionEngine::i_lshl(){}
void ExecutionEngine::i_ishr(){}
void ExecutionEngine::i_lshr(){}
void ExecutionEngine::i_iushr(){}
void ExecutionEngine::i_lushr(){}
void ExecutionEngine::i_iand(){}
void ExecutionEngine::i_land(){}
void ExecutionEngine::i_ior(){}
void ExecutionEngine::i_lor(){}
void ExecutionEngine::i_ixor(){}
void ExecutionEngine::i_lxor(){}
void ExecutionEngine::i_iinc(){}
void ExecutionEngine::i_i2l(){}
void ExecutionEngine::i_i2f(){}
void ExecutionEngine::i_i2d(){}
void ExecutionEngine::i_l2i(){}
void ExecutionEngine::i_l2f(){}
void ExecutionEngine::i_l2d(){}
void ExecutionEngine::i_f2i(){}
void ExecutionEngine::i_f2l(){}
void ExecutionEngine::i_f2d(){}
void ExecutionEngine::i_d2i(){}
void ExecutionEngine::i_d2l(){}
void ExecutionEngine::i_d2f(){}
void ExecutionEngine::i_i2b(){}
void ExecutionEngine::i_i2c(){}
void ExecutionEngine::i_i2s(){}
void ExecutionEngine::i_lcmp(){}
void ExecutionEngine::i_fcmpl(){}
void ExecutionEngine::i_fcmpg(){}
void ExecutionEngine::i_dcmpl(){}
void ExecutionEngine::i_dcmpg(){}
void ExecutionEngine::i_ifeq(){}
void ExecutionEngine::i_ifne(){}
void ExecutionEngine::i_iflt(){}
void ExecutionEngine::i_ifge(){}
void ExecutionEngine::i_ifgt(){}
void ExecutionEngine::i_ifle(){}
void ExecutionEngine::i_if_icmpeq(){}
void ExecutionEngine::i_if_icmpne(){}
void ExecutionEngine::i_if_icmplt(){}
void ExecutionEngine::i_if_icmpge(){}
void ExecutionEngine::i_if_icmpgt(){}
void ExecutionEngine::i_if_icmple(){}
void ExecutionEngine::i_if_acmpeq(){}
void ExecutionEngine::i_if_acmpne(){}
void ExecutionEngine::i_goto(){}
void ExecutionEngine::i_jsr(){}
void ExecutionEngine::i_ret(){}
void ExecutionEngine::i_tableswitch(){}
void ExecutionEngine::i_lookupswitch(){}
void ExecutionEngine::i_ireturn(){}
void ExecutionEngine::i_lreturn(){}
void ExecutionEngine::i_freturn(){}
void ExecutionEngine::i_dreturn(){}
void ExecutionEngine::i_areturn(){}
void ExecutionEngine::i_return(){}
void ExecutionEngine::i_getstatic(){}
void ExecutionEngine::i_putstatic(){}
void ExecutionEngine::i_getfield(){}
void ExecutionEngine::i_putfield(){}
void ExecutionEngine::i_invokevirtual(){}
void ExecutionEngine::i_invokespecial(){}
void ExecutionEngine::i_invokestatic(){}
void ExecutionEngine::i_invokeinterface(){}
void ExecutionEngine::i_new(){}
void ExecutionEngine::i_newarray(){}
void ExecutionEngine::i_anewarray(){}
void ExecutionEngine::i_arraylength(){}
void ExecutionEngine::i_athrow(){}
void ExecutionEngine::i_checkcast(){}
void ExecutionEngine::i_instanceof(){}
void ExecutionEngine::i_monitorenter(){}
void ExecutionEngine::i_monitorexit(){}
void ExecutionEngine::i_wide(){}
void ExecutionEngine::i_multianewarray(){}
void ExecutionEngine::i_ifnull(){}
void ExecutionEngine::i_ifnonnull(){

    Frame *topo = runtimeDataArea->topoPilha();

    Valor referencia = topo->desempilhaOperando();

    assert(referencia.tipo == TipoDado::REFERENCE);

    if ((Objeto*)(referencia.dado) != NULL) {
        uint8_t *code = topo->getCode();
        uint8_t byte1 = code[1];
        uint8_t byte2 = code[2];
        int16_t salto =  (byte1 << 8) | byte2;
        topo->incrementaPC(salto);
    }
    else {

        topo->incrementaPC(3);

    }



}

void ExecutionEngine::i_goto_w(){

	Frame *topo = runtimeDataArea->topoPilha();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint8_t byte3 = code[3];
	uint8_t byte4 = code[4];
	int32_t offsetSalto = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

	topo->incrementaPC(offsetSalto);
	assert(topo->getPC() < (int32_t)topo->tamanhoCode());

}

void ExecutionEngine::i_jsr_w(){

	Frame *topo = runtimeDataArea->topoPilha();

	uint8_t *code = topo->getCode();
	uint8_t byte1 = code[1];
	uint8_t byte2 = code[2];
	uint8_t byte3 = code[3];
	uint8_t byte4 = code[4];
	int32_t offsetSalto = (byte1 << 24) | (byte2 << 16) | (byte3 << 8)| byte4;

	Valor endRetorno;
	endRetorno.tipo = TipoDado::RETURN_ADDR;
	endRetorno.dado = topo->getPC() + 5;
	topo->empilharOperando(endRetorno);

	topo->incrementaPC(offsetSalto);
	assert(topo->getPC() < (int32_t)(topo->tamanhoCode()));


}
