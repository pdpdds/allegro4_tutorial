/*
												AlSub

									por Eduardo "Dudaskank"
								-----------------------------

		Este software � LGPL, veja os detalhes em docs/lgpl.txt

		Implementa��o da classe ALSUB_TEXT

*/

#include "alsub.h"

/* construtor
*/
ALSUB_TEXT::ALSUB_TEXT(const int &ini, const int &end, const std::string &text)
{
	set(ini, end, text);
}


/* contrutor c�pia
*/
ALSUB_TEXT::ALSUB_TEXT(const ALSUB_TEXT &ast)
{
	set(ast.ini, ast.end, ast.text);
}


/* destrutor
*/
ALSUB_TEXT::~ALSUB_TEXT()
{
}


/* seta as vari�veis da classe, 'ini' e 'end' s�o os quadros de in�cio e fim,
	e 'text' � a string que ser� mostrada
*/
void ALSUB_TEXT::set(const int &ini, const int &end, const std::string &text)
{
	this->ini = ini;
	this->end = end;
	this->text = text;
}


/* copia os atributos da classe para as vari�veis apontadas por 'ini', 'end' e 'text'
*/
void ALSUB_TEXT::get(int *ini, int *end, std::string *text)
{
	*ini = this->ini;
	*end = this->end;
	*text = this->text;
}


/* sobrecarga do operador ==, compara todos os campos
*/
bool ALSUB_TEXT::operator ==(const ALSUB_TEXT &ast)
{
	return (ini == ast.ini && end == ast.end && text == ast.text);
}


/* sobrecarga do operador <, usado no m�todo 'list_text::sort', compara os
	atributos 'ini' das classes
*/
bool ALSUB_TEXT::operator <(const ALSUB_TEXT &ast)
{
	return (ini < ast.ini);
}
