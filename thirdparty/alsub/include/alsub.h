/*
												AlSub

									por Eduardo "Dudaskank"
								-----------------------------

		Este software é LGPL, veja os detalhes em docs/lgpl.txt

		Tipos, macros e definições de classes para a biblioteca AlSub

*/

#ifndef _ALSUB_H
#define _ALSUB_H

/* para usar strings sem entrar em conflito com o Allegro */
#define __GTHREAD_HIDE_WIN32API
#include <allegro.h>
#include <string>
#include <list>


#define ALSUB_VERSION				0
#define ALSUB_SUB_VERSION			1
#define ALSUB_WIP_VERSION			0
#define ALSUB_VERSION_STR			"0.1.0"
#define ALSUB_DATE_STR				"2003"
#define ALSUB_DATE					20030205		/* yyyymmdd */


/* classe ALSUB_TEXT
	contém as informações para cada legenda que aparece
*/
class ALSUB_TEXT {
	private:

	int ini, end;							/* frames de início e fim */
	std::string text;						/* texto que será mostrado */

	public:

	ALSUB_TEXT(const int &ini = 0, const int &end = 0, const std::string &text = "");
	ALSUB_TEXT(const ALSUB_TEXT &ast);
	~ALSUB_TEXT();

	void set(const int &ini = 0, const int &end = 0, const std::string &text = "");
	void get(int *ini, int *end, std::string *text);
	bool operator ==(const ALSUB_TEXT &ast);
	bool operator <(const ALSUB_TEXT &ast);
};


/* alinhamento horizontal
*/
enum ALSUB_HALIGN {
	LEFT = 0,
	CENTER,
	RIGHT
};


/* alinhamento vertical
*/
enum ALSUB_VALIGN {
	TOP = 0,
	MIDDLE,
	BOTTOM
};


/* lista de ALSUB_TEXT
*/
typedef std::list<ALSUB_TEXT> list_text;


/* classe principal ALSUB
	contém todas as legendas, pode adicionar/deletar, importar/exportar e
	converter entre diferentes taxas de quadros por segundo
*/
class ALSUB{
	private:

	list_text texts;						/* todas as legendas */
	list_text::iterator it;				/* posição atual na lista */
	int cur_frame;							/* número do quadro atual */

	public:

	ALSUB();
	~ALSUB();

	void insert_text(const ALSUB_TEXT &ast);
	void insert_text(const int &ini = 0, const int &end = 0, const std::string &text = "");
	void delete_text(const ALSUB_TEXT &ast);
	void delete_text(const int &ini = 0, const int &end = 0, const std::string &text = "");
	void update_frame(int frame);
	void reset_frame(void);
	void inc_frame(void);
	void dec_frame(void);
	void display(BITMAP *bmp, const FONT *fonte = font, int x = 0, int y = 0, int c = 0,
		int borderc = -1, ALSUB_HALIGN halign = LEFT, ALSUB_VALIGN valign = TOP);
	int load(const char *file);
	int save(const char *file);
	void convert(const float &afps, const float &nfps);
};


#endif // _ALSUB_H
