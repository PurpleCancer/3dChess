/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

const float PI = 3.141592653589793f;

//STALE OKNA
const int WINDOWWIDTH = 1280;
const int WINDOWHEIGHT = 800;


//STALA PLANSZY
const int TILECOUNT=8;

const float BOARDHEIGHTRATIO = 0.05;
const float BOARDSIDESIZE= 16;
const float BOARDSCALE=0.5*BOARDSIDESIZE;


const float PIECESIZE=BOARDSIDESIZE/TILECOUNT;
const float PIECESCALE=0.5*PIECESIZE;

const float TILESIZE=BOARDSIDESIZE/TILECOUNT;

const float PIECEMOVINGCONSTANT=0.5f*BOARDSIDESIZE-0.5f*TILESIZE;


const float BREAKBETWEENMOVES = 1.0f;

const int PIECESAMOUNT=6;
const int TEXTURESAMOUNT=3;


#endif
