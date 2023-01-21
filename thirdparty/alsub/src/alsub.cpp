/*!
												AlSub

								vers? 0.1 por Eduardo "Dudaskank"
								----------------------------------

		Este software ?LGPL, veja os detalhes em docs/lgpl.txt

		Implementação da classe principal ALSUB

*/

//#define DEBUGMODE
#include "alsub.h"
#include <stdio.h>


/* construtor
*/
ALSUB::ALSUB()
{
	cur_frame = 0;
	//it = list_text.end();
}


/* destrutor
*/
ALSUB::~ALSUB()
{
}


/* insere uma nova legenda na lista e ordena
*/
void ALSUB::insert_text(const ALSUB_TEXT &ast)
{
	texts.push_back(ast);
	texts.sort();
	/* reinicia a posição de 'it' */
	it = texts.begin();
}


/* insere uma nova legenda na lista e ordena, onde 'ini' e 'end' s? os quadros
	de in?io e fim e 'text' ?o texto que ser?apresentado durante o intervalo
*/
void ALSUB::insert_text(const int &ini, const int &end, const std::string &text)
{
	ALSUB_TEXT ast(ini, end, text);
	insert_text(ast);
}


/* deleta a legenda que for igual ?'ast'
*/
void ALSUB::delete_text(const ALSUB_TEXT &ast)
{
	texts.remove(ast);
	/* reinicia o iterador 'it' */
	it = texts.begin();
}


/* deleta a legenda que for igual ?criada por 'ini', 'end' e 'text'
*/
void ALSUB::delete_text(const int &ini, const int &end, const std::string &text)
{
	ALSUB_TEXT ast(ini, end, text);
	delete_text(ast);
}


/* atualiza o quadro, mudando o posicionamento de 'it' se for necess?io
*/
void ALSUB::update_frame(int frame)
{
	int ini, end;
	std::string str;

	/* guarda nova posição */
	cur_frame = frame;

	/* se n? tiver nada na lista, retorna */
	if(texts.size() == 0) {
		return;
	}

	/* se estiver no final, retorna 1 */
	if(it == texts.end()) {
		--it;
	}

	/* se for a primeira vez, inicia no come? da lista */
	if(it ==texts.end()) {
		it = texts.begin();
	}

	/* enquanto o quadro atual estiver antes do apontado por 'it', volta at?que
		isto n? ocorra mais ou chegar no in?io da lista */
	(*it).get(&ini, &end, &str);
	while(cur_frame < ini && it != texts.end()) {
		if(it == texts.begin())
			break;
		it--;
		(*it).get(&ini, &end, &str);
	}
	/* enquanto o quadro atual estiver depois do apontado por 'it', avan? at?que
		isto n? ocorra mais ou chegar no final da lista */
	while(cur_frame > end && it != texts.end()) {
		it++;
		if(it == texts.end())
			break;
		(*it).get(&ini, &end, &str);
	}
}


/* reinicia o valor do quadro atual para 0 e 'it' para nulo
*/
void ALSUB::reset_frame(void)
{
	it = texts.end();
	update_frame(0);
}


/* aumenta em 1 o valor do quadro atual
*/
void ALSUB::inc_frame(void)
{
	update_frame(cur_frame + 1);
}


/* diminui em 1 o valor do quadro atual
*/
void ALSUB::dec_frame(void)
{
	update_frame(cur_frame - 1);
}


/* desenha a legenda atual em 'bmp', usando a fonte 'fonte' na posição 'x', 'y',
	com a cor 'c', levando em conta o alinhamento horizontal 'halign' e o alinhamento
	vertical 'valign'> A vari?el 'borderc', se diferente de -1, ?a cor da borda.
	Lembre-se que quando usar borda o text_mode() deve estar com -1.
*/
void ALSUB::display(BITMAP *bmp, const FONT *fonte, int x, int y, int c, int borderc,
	ALSUB_HALIGN halign, ALSUB_VALIGN valign)
{
	/* ponteiro para função que ser?utilizado para imprimir o texto */
	void (*textprint)(BITMAP *, const FONT *, const char *, int, int, int);
	std::string text;
	char *linha;
	char *buffer;
	int ini, end;
	int fonte_h, i, l = 1;

	/* se estiver no fim da lista, volta */
	if(it == texts.end())
		return;

	/* l?as informações da legenda atual */
	(*it).get(&ini, &end, &text);

	/* se o quadro atual estiver no intervalo entre 'ini' e 'end', continua */
	if(ini <= cur_frame && end >= cur_frame) {
		/* armazena o valor da altura da fonte para uso posterior */
		fonte_h = text_height(fonte);

		/* verifica o alinhamento horizontal e seta o ponteiro para a função
			baseado neste alinhamento */
		switch(halign) {
			case LEFT :
				textprint = textout;
			break;
			case CENTER :
				textprint = textout_centre;
			break;
			case RIGHT :
				textprint = textout_right;
			break;
			default :
				textprint = textout;
			break;
		}
		/* cria um buffer tempor?io e copia a string nele */
		buffer = new char[strlen(text.c_str())+1];
		strcpy(buffer, text.c_str());
		acquire_bitmap(bmp);

		/* conta as linhas usadas pela string caso valign seja diferente de TOP.
			Observe que cada linha ?separada por um caractere '|' */
		if(valign != TOP) {
			for(i = 0, l = 1; i < (signed)strlen(buffer); i++) {
				if(buffer[i] == '|') {
					l++;
				}
			}
		}

		/* verifica o alinhamento vertical e ajusta o 'y' conforme necess?io */
		switch(valign) {
			case MIDDLE :
				/* recalcula o 'y', baseado na quantidade de linhas */
				y -= l*fonte_h/2;
			break;
			case BOTTOM :
				/* recalcula o 'y', baseado na quantidade de linhas */
				y -= l*fonte_h;
			break;
			default :
				/* quando 'valign' ?TOP, n? precisa recalcular */
			break;
		}
		/* cada linha de texto ?separada por '|' */
		linha = strtok(buffer, "|");
		if(linha) {
			/* se 'borderc' for diferente de -1, desenha com borda o texto */
			if(borderc != -1) {
				textprint(bmp, fonte, linha, x+1, y, borderc);
				textprint(bmp, fonte, linha, x-1, y, borderc);
				textprint(bmp, fonte, linha, x, y+1, borderc);
				textprint(bmp, fonte, linha, x, y-1, borderc);
			}
			textprint(bmp, fonte, linha, x, y, c);
			y += fonte_h;
		}
		do {
			linha = strtok(0, "|");
			if(linha) {
				/* se 'borderc' for diferente de -1, desenha com borda o texto */
				if(borderc != -1) {
					textprint(bmp, fonte, linha, x+1, y, borderc);
					textprint(bmp, fonte, linha, x-1, y, borderc);
					textprint(bmp, fonte, linha, x, y+1, borderc);
					textprint(bmp, fonte, linha, x, y-1, borderc);
				}
				textprint(bmp, fonte, linha, x, y, c);
				y += fonte_h;
			}
		} while(linha);

		release_bitmap(bmp);
		/* deleta o buffer alocado antes */
		delete []buffer;
	}
}


/* carrega um arquivo no formato '.sub'
*/
int ALSUB::load(const char *file)
{
	PACKFILE *f;
	char buffer[512], *str = 0;
	int ini, end, i, c;

	/* abre o arquivo em modo de leitura */
	f = pack_fopen(file, F_READ);
	if(!f) {
		return 1;
	}

	/* limpa a lista atual */
	texts.clear();
	/* enquanto n? acabar... */
	while(!pack_feof(f)) {
		/* l?uma linha */
		if(pack_fgets(buffer, 512, f)) {
			/* l?2 inteiros entre '{' e '}' (ex: {1}{20}) */
			if(sscanf(buffer, "{%d}{%d}", &ini, &end) == 2) {
				/* procura pelo 2?'}' e faz 'str' apontar pro pr?imo e parar */
				for(c = 0, i = 0; buffer[i]; i++) {
					if(buffer[i] == '}') {
						c++;
					}
					if(c == 2) {
						str = &buffer[i+1];
						break;
					}
				}
				/* insere a legenda */
				insert_text(ini, end, str);
			}
		}
	}
	/* fecha o arquivo */
	pack_fclose(f);

	return 0;
}


/* salva um arquivo no formato '.sub'
*/
int ALSUB::save(const char *file)
{
	PACKFILE *f;
	list_text::iterator i;
	int ini, end;
	std::string s;
	char buffer[512];

	/* abre o arquivo em modo de escrita */
	f = pack_fopen(file, F_WRITE);
	if(!f) {
		return 1;
	}

	/* percorre toda a lista */
	for(i = texts.begin(); i != texts.end(); i++) {
		/* pega os valores daquela posição */
		(*i).get(&ini, &end, &s);
		/* imprime num 'buffer' no formato apropriado */
		sprintf(buffer, "{%d}{%d}%s\n", ini, end, s.c_str());
		/* imprime o 'buffer' no arquivo */
		pack_fputs(buffer, f);
	}
	/* fecha o arquivo */
	pack_fclose(f);
	return 0;
}


/* converte entre duas taxas de quadros por segundo diferentes, onde 'afps' ?
	a taxa atual e 'nfps' ?a nova taxa
*/
void ALSUB::convert(const float &afps, const float &nfps)
{
	list_text::iterator i;
	float factor;
	int ini, end;
	std::string str;

	/* calcula o fator */
	factor = nfps / afps;
	for(i = texts.begin(); i != texts.end(); i++) {
		/* pega os valores atuais */
		(*i).get(&ini, &end, &str);
		/* multiplica o in?io e o fim pelo fator */
		ini = (int)(ini*factor);
		end = (int)(end*factor);
		/* atualiza com os novos valores */
		(*i).set(ini, end, str);
	}
}
