#include "method_info.hpp"
#include"Leitura.hpp"
#include<iostream>

method_info::method_info(FILE *arq, std::vector<cp_info*> const &constant_pool)
{
	using namespace Leitura;
	
	LerAtributo(&access_flags, 2, arq);
	LerAtributo(&name_index, 2, arq);
	LerAtributo(&descriptor_index, 2, arq);
	LerAtributo(&attributes_count, 2, arq);
cout<< "Lerei "<< attributes_count << "  attribute_infos" << endl;
	for(int cont =0; cont < attributes_count; cont++)
	{
		attribute_info *p= attribute_info::LerAtributeInfo(arq, constant_pool);
cout<< "criado elemento attribute_info" << endl;
		attributes.push_back(p);
	}
}

void method_info::ExibirInformacoes(string tabs)
{
	cout << tabs << "access_flags =\t\t" << access_flags << endl;
	if(access_flags & 0x0001)
	{
		cout << tabs << "\tACC_PUBLIC" << endl;
	}
	if(access_flags & 0x0002)
	{
		cout << tabs << "\tACC_PRIVATE" << endl;
	}
	if(access_flags & 0x0004)
	{
		cout << tabs << "\tACC_PROTECTED" << endl;
	}
	if(access_flags & 0x0008)
	{
		cout << tabs << "\tACC_STATIC" << endl;
	}
	if(access_flags & 0x0010)
	{
		cout << tabs << "\tACC_FINAL" << endl;
	}
	if(access_flags & 0x0020)
	{
		cout << tabs << "\tACC_SYNCHRONIZED" << endl;
	}
	if(access_flags & 0x0040)
	{
		cout << tabs << "\tACC_BRIDGE" << endl;
	}
	if(access_flags & 0x0080)
	{
		cout << tabs << "\tACC_VARARGS" << endl;
	}
	if(access_flags & 0x0100)
	{
		cout << tabs << "\tACC_NATIVE" << endl;
	}
	if(access_flags & 0x0400)
	{
		cout << tabs << "\tACC_ABSTRACT" << endl;
	}
	if(access_flags & 0x0800)
	{
		cout << tabs << "\tACC_STRICT" << endl;
	}
	if(access_flags & 0x1000)
	{
		cout << tabs << "\tACC_SYNTHETIC" << endl;
	}
	cout << tabs << "name_index =\t\t" << name_index << endl;
	cout << tabs << "descriptor_index =\t" << descriptor_index << endl;
	cout << tabs << "attributes_count =\t" << attributes_count << endl;
	if(attributes.size() > 0)
	{
		cout << tabs << "Attributes:"<<endl;
		cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
		for(int cont =0; cont < attributes_count; cont++)
		{
			cout << tabs << "\tAttributes[" << cont << "]:" << endl;;
			attributes[cont]->ExibirInformacoes( ( (tabs + "\t") +"\t" ) );
			if(cont < attributes_count -1)
			{
				cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -" << endl;
			}
		}
	}
}
