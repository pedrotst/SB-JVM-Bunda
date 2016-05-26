#include<stdint.h>
#include<stdio.h>
#include<vector>

#ifndef ATTRIBUTE_INFO_HPP
#define ATTRIBUTE_INFO_HPP

class attribute_info
{
	protected:
		uint16_t attribute_name_index;
		uint32_t attribute_length;
//	uint8_t *info;

	public:
	static attribute_info * LerAtributeInfo(FILE *arq);
	virtual void ExibirInformacoes(void)=0;
};

namespace Atributos
{
	using namespace std;

	class ConstantValue_attribute: public attribute_info
	{
		private:
			uint16_t constantvalue_index;
		public:
			ConstantValue_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Excecao
	{
		private:
			uint16_t start_pc;
			uint16_t end_pc;
			uint16_t handler_pc;
			uint16_t catch_type;
		public:
			Excecao(FILE *arq);
			void ExibirInformacoes(void);
	};

	class Code_attribute: public attribute_info
	{
		private:
			uint16_t max_stack;
			uint16_t max_locals;
			uint32_t code_length;
			uint8_t *code;
			uint16_t exception_table_length;
			vector<Excecao> exception_table;
			uint16_t attributes_count;
			vector<attribute_info *> attributes;
		public:
			Code_attribute(FILE *arq, uint16_t attributeNameIndex);
			~Code_attribute(void);
			void ExibirInformacoes(void);
	};

	class StackMapTable_attribute: public attribute_info
	{
		public:
			uint16_t number_of_entries;
	//			vector<stack_map_frame> entries;
	};

	class Exceptions_attribute : public attribute_info
	{
		private:
			uint16_t number_of_exceptions;
			vector<uint16_t> exception_index_table;
	
		public:
			Exceptions_attribute (FILE *arq, uint16_t attributeNameIndex);
			~Exceptions_attribute ();
			void ExibirInformacoes(void);
	};

	class InfoDaClasse
	{
		private:
			uint16_t inner_class_info_index;
			uint16_t outer_class_info_index;
			uint16_t inner_name_index;
			uint16_t inner_class_access_flags;
		public:
			InfoDaClasse(FILE *arq);
			void ExibirInformacoes(void);
	};

	class InnerClasses_attribute: public attribute_info
	{
		private:
			uint16_t number_of_classes;
			vector<InfoDaClasse> classes;
		public:
			InnerClasses_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class EnclosingMethod_attribute:public attribute_info
	{
		private:
			uint16_t class_index;
			uint16_t method_index;
		public:
			EnclosingMethod_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes();
	};

	class Synthetic_attribute: public attribute_info
	{
		private:
		public:
			Synthetic_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Signature_attribute:public attribute_info
	{
		private:
			uint16_t signature_index;
		public:
			Signature_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class SourceFile_attribute: public attribute_info
	{
		private:
			uint16_t sourcefile_index;
		public:
			SourceFile_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class SourceDebugExtension_attribute: public attribute_info
	{
		private:
			uint8_t *debug_extension;
		public:
			SourceDebugExtension_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Elemento_LineNumber
	{
		private:
			uint16_t start_pc;
			uint16_t line_number;
		public:
			Elemento_LineNumber(FILE *arq);
			void ExibirInformacoes(void);
	};

	class LineNumberTable_attribute: public attribute_info
	{
		private:
			uint16_t line_number_table_length;
			vector<Elemento_LineNumber> elements_number_table;
		public:
			LineNumberTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Elemento_local_variable
	{
		private:
			uint16_t start_pc;
			uint16_t length;
			uint16_t name_index;
			uint16_t descriptor_index;
			uint16_t index;
		public:
			Elemento_local_variable(FILE *arq);
			void ExibirInformacoes(void);
	};

	class LocalVariableTable_attribute : public attribute_info
	{
		private:
			uint16_t local_variable_table_length;
			vector<Elemento_local_variable> local_variable_table;
		public:
			LocalVariableTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};

	class Elemento_LocalVariableType
	{
		private:
			uint16_t start_pc;
			uint16_t length;
			uint16_t name_index;
			uint16_t signature_index;
			uint16_t index;
		public:
			Elemento_LocalVariableType(FILE *arq);
	};

	class LocalVariableTypeTable_attribute : public attribute_info
	{
		private:
			uint16_t local_variable_type_table_length;
			vector<Elemento_LocalVariableType>local_variable_type_table;
		public:
			LocalVariableTypeTable_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};


	class Deprecated_attribute : public attribute_info
	{
		public:
		private:
			Deprecated_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
	};
	
	class Elemento_Metodo_Bootstrap
	{
		private:
			uint16_t bootstrap_method_ref;
			uint16_t num_bootstrap_arguments;
			vector<uint16_t> bootstrap_arguments;
		public:
			Elemento_Metodo_Bootstrap(FILE *arq);
			void ExibirInformacoes(void);
	}
	
	class BootstrapMethods_attribute: public attribute_info
	{
		private:
			uint16_t num_bootstrap_methods;
			vector<Elemento_Metodo_Bootstrap>bootstrap_methods;
		public:
			BootstrapMethods_attribute(FILE *arq, uint16_t attributeNameIndex);
			void ExibirInformacoes(void);
}

//	class 
/*
	class annotation
	{
		uint16_t type_index;
		uint16_t num_element_value_pairs;
 element_value_pairs[num_element_value_pairs];
	}
*/
}
#endif
