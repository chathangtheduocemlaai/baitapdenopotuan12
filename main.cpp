#include <SDL.h>
#include<iostream>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<vector>
#include<math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include<fstream>


using namespace std ;
float absd(float x)
{
    if(x > 0.0) return x ;
    return - x ;
}
int gioihan(int x)
{
    switch(x)
    {
        case 1 : return 0 ; break ;
        case 2 : return 1 ; break ;
        case 3 : return 1 ; break ;
        case 4 : return 2 ; break ;
        case 5 : return 2 ; break ;
        case 6 : return 3 ; break ;
        case 7 : return 3 ; break ;
        case 8 : return 4 ; break ;
        case 9 : return 4 ; break ;
       // case 10 : return 0 ; break ;

    }
}

int soluongchim(int x)
{
    switch(x)
    {
        case 1 : return 8 ; break ;
        case 2 : return 10 ; break ;
        case 3 : return 6 ; break ;
        case 4 : return 14 ; break ;
        case 5 : return 12 ; break ;
        case 6 : return 10 ; break ;
        case 7 : return 10 ; break ;
        case 8 : return 22 ; break ;
        case 9 : return 10 ; break ;
       // case 10 : return 0 ; break ;

    }
}

string doi_so_sang_text(int a)
{
    string ans = "" ; int du ;
    while(a >0)
    {
        du = a % 10 ;
        char c = du +'0' ;
        ans = c + ans ;
        a  = a /10 ;
    }
    return ans ;
}

int random(int minN, int maxN){
 return minN + rand() % (maxN + 1 - minN);
}

const float SCREEN_WIDTH = 1200;
const float SCREEN_HEIGHT = 600;
int  vel_chim = 0 ;
SDL_Window *gwindow = NULL ;
SDL_Renderer *grenderer = NULL ;
SDL_Surface *gsurface = NULL ;
TTF_Font *gfont = NULL;



SDL_Event e ;
void init()
{
    gwindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) ;

    SDL_SetRenderDrawColor( grenderer, 0xFF, 0xFF, 0xFF, 0xFF );
}
void close()
{
	//Destroy window
	SDL_DestroyRenderer( grenderer );
	SDL_DestroyWindow( gwindow );
	gwindow = NULL;
	grenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/* class Base */
class Base
{
public:
    Base() ;
    ~Base() ;
    void free() ;
    void loadfromfile(string path) ;
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
		//Set blending
    void setBlendMode( SDL_BlendMode blending );
		//Set alpha modulation
    void setAlpha( Uint8 alpha );

    void setrect(float x, float y) ;
    int hp ;

    void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE ) ;
    float get_pos_x(){return mPosx;}; float get_pos_y(){return mPosy;};float get_width(){return mWidth;}; float get_height(){return mHeight;};
    void set_hp(int x) {hp = x;};



protected:
    SDL_Texture *mTexture ;
    float mWidth , mHeight, mPosx, mPosy ;

};
void Base::free()
{
    if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
Base::Base()
{
    mTexture = NULL ;
    mWidth = 0 ;
    mHeight = 0 ;
    mPosx = 0 ;
    mPosy = 0 ;
}
Base::~Base()
{
    free() ;
}
void Base::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}
void Base::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
void Base::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
void Base::loadfromfile(string path)
{
    free() ;
    SDL_Surface *image_surface = IMG_Load(path.c_str());
    //SDL_Surface *optimizedSurface = SDL_ConvertSurface( image_surface,image_surface->format,0 );
    SDL_SetColorKey( image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 0, 0xFF, 0xFF ) );
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(grenderer,image_surface) ;
    mWidth = image_surface->w ;
    mHeight = image_surface -> h ;
    mTexture = image_texture ;
    SDL_FreeSurface(image_surface);
}
void Base::setrect(float x, float y)
{
    mPosx = x ;
    mPosy = y ;
}
void Base::render( SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosx, mPosy, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( grenderer, mTexture, clip, &renderQuad, angle, center, flip );

}
/* CLASS TEXT */
class TextObject : public Base
{
public:
    enum TextColor
    {
        RED_TEXT = 0 ,
        WHITE_TEXT = 1 ,
        BLACK_TEXT = 2 ,
    };
    TextObject() ;
    ~TextObject() ;
    void Set_Text(string path1) ;
    void Set_Color(int type) ;
    void loadFromRenderedText();
    void Show_Text(){cout << text;} ;
private:
    string text ;
    SDL_Color text_color ;
};
TextObject::TextObject()
{
    mTexture = NULL ;
    mWidth = 0 ;
    mHeight = 0 ;
    mPosx = 500;
    mPosy = 200 ;
    text = "" ;
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;

}
TextObject::~TextObject()
{

}
void TextObject::loadFromRenderedText()
{
	//Get rid of preexisting texture
	free();
	//Render text surface
	SDL_Surface* textSurface; textSurface = TTF_RenderText_Solid( gfont, text.c_str(), text_color);
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( grenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else cout << "LOI" ;
}
void TextObject::Set_Text(string path1)
{
    text = path1 ;
}
void TextObject::Set_Color(int type)
{
    if (type == RED_TEXT)
  {
    SDL_Color color = {255, 0, 0,0xFF};
    text_color = color;
  }
  else if (type == WHITE_TEXT)
  {
    SDL_Color color = {255, 255, 255,0xFF};
    text_color = color;
  }
  else
  {
    SDL_Color color = {0, 0, 0,0xFF};
    text_color = color;
  }

}
TextObject Score ;


/*CLASS BULLET */
class Bullet:public Base
{
public:
    Bullet() ;
    ~Bullet() ;
    bool get_move() ;
    void set_up_or_down(bool l);
    void MouseAction() ;
    void BulletMove() ;
    void SetVel(float x , float y ) ;
    bool da_lay_muctieu ;
    void get_muctieu(float x, float y) {muctieu_x = x ; muctieu_y = y ;}

private:
    bool ismove, up_or_down ;
    float vel_bullet_x ;
    float vel_bullet_y ;
    float muctieu_x, muctieu_y ;



};
void Bullet::set_up_or_down(bool l)
{
    up_or_down = l ;
}
Bullet::Bullet()
{
    vel_bullet_x = 0 ;
    vel_bullet_y = 0 ;
    mPosx = 1200 ;
    mPosy = 0 ;
    ismove = true  ;
    da_lay_muctieu = false ;
    muctieu_x = 0 ;
    muctieu_y = 0 ;

}
Bullet::~Bullet()
{

}
void Bullet::SetVel(float x, float y)
{
    vel_bullet_x = x ;
    vel_bullet_y = y ;
}
bool Bullet::get_move()
{
    return ismove ;
}
void Bullet::MouseAction()
{

}
void Bullet::BulletMove()
{
    if(up_or_down)
    {
        mPosx += vel_bullet_x ;
        mPosy += vel_bullet_y ;
        if(mPosx > 1200 || mPosx <0 || mPosy > 600 || mPosy <0)
        {
            ismove = false ;

        }
    }
    else
    {

        if(mPosx > 1200 || mPosx <0  || mPosy <0 || mPosy > 800)
        {
            ismove = false ;

        }

        mPosx += vel_bullet_x ;
        mPosy += vel_bullet_y;


    }
}

/*CLASS MAINOBJECT */

class MainObject: public Base
{
public:
    MainObject() ;
    ~MainObject() ;

    bool lorr(SDL_Event &e) ;

    float vel = 5 ;
    void HandleAction(SDL_Event &e) ;
    void HandleMove() ;
    vector<Bullet> Bul ;

private:
    float mVelx, mVely ;




};
MainObject::MainObject()
{
    mVelx = 0 ;
    mPosy = 423 ;
    mPosx = 600 ;
    mVely = 0 ;
    hp = 100  ;
}
MainObject::~MainObject()
{
}
bool MainObject::lorr(SDL_Event &e)
{
    //if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        if(e.key.keysym.sym == SDLK_a )
        {
            return false ;
        }
        else if(e.key.keysym.sym == SDLK_d)
        {
            return true ;
        }
    }
    if(e.type == SDL_KEYUP && e.key.repeat == 0)
           {
        //Adjust the velocity
        if(e.key.keysym.sym == SDLK_a)
        {
            return false ;
        }
        else if(e.key.keysym.sym == SDLK_d)
        {
            return true ;
        }
    }
}
void MainObject::HandleAction( SDL_Event &e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

        case SDLK_UP:
            {
                for(float i = 1 ; i <= 100 ; i++)
                {
                    mPosy -= 1 ;
                }
                break;
            }
            //case SDLK_DOWN: mVely += vel; break;
            case SDLK_a: mVelx -=10 ; break;
            case SDLK_d: mVelx +=10; break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {

            case SDLK_UP:
                {
                    for(float i =1 ; i <= 100 ; i++)
                    {
                        mPosy += 1 ;
                    }
                    break;
                };
            //case SDLK_DOWN: mVely -= vel; break;
            case SDLK_a: mVelx +=10 ; break;
            case SDLK_d: mVelx -= 10  ; break;
        }
    }

    else if(  e.type == SDL_MOUSEBUTTONDOWN )
    {
        int x1, y1;
        SDL_GetMouseState(&x1,&y1) ; float x = x1 , y = y1 ;
        Bullet new_bul ;
        new_bul.setrect(mPosx,mPosy) ;
        new_bul.SetVel((x-mPosx)/abs(x-mPosx)*10  , (y-mPosy)/abs(x-mPosx)*10) ;
        //cout << (x-mPosx)/abs(x-mPosx)*10  << " " <<  (y-mPosy)/abs(x-mPosx)*10 << endl ;

        Bul.push_back(new_bul) ;

    }
}
void MainObject::HandleMove()
{
    //Move the dot left or right
    mPosx += mVelx;
    //If the dot went too far to the left or right
    if( ( mPosx < 0 ) || ( mPosx + mWidth > SCREEN_WIDTH ) )
    {
        //Move back
        mPosx -= mVelx;
    }
    //Move the dot up or down
    mPosy += mVely;

    //If the dot went too far up or down

}
 MainObject human ;
/* ClASS Threast */
class Threat : public Base
{
public:

    Threat() ;
    ~Threat() ;
    void threat_move() ;
    vector<Bullet> Bul ;
    void set_vector_move(bool l) {move_left_or_right = l ; }
    bool get_vector() {return move_left_or_right ;}
    //int get_pos_cum() {return pos_cum;}
private:
    float vel_threat_x ;
    float vel_threat_y ;
    int pos_cum1, pos_cum2, pos_cum3 ;
    bool move_left_or_right ;

};
Threat::Threat()
{
    mPosx = 1200 ;
    mPosy = 200 ;
    pos_cum1 = 1200 ;
    pos_cum2 = 1200 ;
    pos_cum3 = 1200 ;
}
Threat::~Threat()
{

}
void Threat::threat_move()
{

if(move_left_or_right == false ){
    if(mPosx == 0)
    {
        pos_cum1 = random(0,1200)/5*5 ;
        pos_cum2 = random(0,1200)/5*5 ;
       // pos_cum3 = random(0,1200)/5*5 ;

    }
    mPosx += -5 + vel_chim ;
    mPosy = random(mPosy -3, mPosy +3) ;
    if(mPosx < 0)
    {
        mPosx = 3000;
        mPosy = random(20,200) ;
        hp = 20 ;
        //ismove = false ;
    }
    if(mPosx == pos_cum1 ||mPosx == pos_cum2  )
    {
        Bullet new_bul ;
        new_bul.setrect(mPosx, mPosy) ;
        new_bul.set_up_or_down(false) ;
        Bul.push_back(new_bul) ;
    }
}
else
{
    if(mPosx == 0)
    {
        pos_cum1 = random(0,1200)/5*5 ;
        pos_cum2 = random(0,1200)/5*5 ;
      //  pos_cum3 = random(0,1200)/5*5 ;

    }
    mPosx += 5 + vel_chim ;
    mPosy = random(mPosy -3, mPosy +3) ;
    if(mPosx >1200)
    {
        mPosx = -1800 ;
        mPosy = random(20,200) ;
        hp = 20 ;
        //ismove = false ;
    }
    if(mPosx == pos_cum1 ||mPosx == pos_cum2 )
    {
        Bullet new_bul ;
        new_bul.setrect(mPosx, mPosy) ;
        new_bul.set_up_or_down(false) ;
        Bul.push_back(new_bul) ;
    }

}


}
bool CheckCollision( Threat object1,  Bullet object2)
{
  float left_a = object1.get_pos_x();
  float right_a = object1.get_pos_x() + object1.get_width();
  float top_a = object1.get_pos_y();
  float bottom_a = object1.get_pos_y() + object1.get_height();

  int left_b = object2.get_pos_x();
  int right_b = object2.get_pos_x() + object2.get_width();
  int top_b = object2.get_pos_y();
  int bottom_b = object2.get_pos_y() + object2.get_height();

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}
bool CheckCollision1( MainObject object1,  Bullet object2)
{
  float left_a = object1.get_pos_x();
  float right_a = object1.get_pos_x() + object1.get_width();
  float top_a = object1.get_pos_y();
  float bottom_a = object1.get_pos_y() + object1.get_height();

  int left_b = object2.get_pos_x();
  int right_b = object2.get_pos_x() + object2.get_width();
  int top_b = object2.get_pos_y();
  int bottom_b = object2.get_pos_y() + object2.get_height();

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}

Base pause ;
TextObject text_level , text_hp, text_task ;
bool win_task = false, pause_game = false ;
int level, so_luong_chim, gioi_han_tren, kiem_soat_gioi_han, task ;
vector<string> list_chim {"chim_nau.png","chim_vang.png","chim_bom.png","chim_xanh.png","pig_fly.png"};

/* Main */
int main(int argc, char* argv[])
{
    /* xu ly level */
    ifstream ip ("du_lieu_game.txt") ;
    ofstream op ("du_lieu_game1.txt") ;
    if(ip)
    {
        cout << " success " ;
    }
    ip >> level ;

    /* kiem_soat_chim */
    if(level % 2 == 0)
    {
        kiem_soat_gioi_han = 0 ;
    }
    else
    {
        kiem_soat_gioi_han = 1 ;
    }

    task = 5 + level * 5 ;




    gioi_han_tren = gioihan(level)   ;
    so_luong_chim = soluongchim(level)  ;

    string chim_at_level[so_luong_chim] ;
    for(int i = 0 ; i < so_luong_chim ; i++)
    {
        if(i % 2 == 0 )
        {
            chim_at_level [i] = list_chim[gioi_han_tren - 1 + kiem_soat_gioi_han] ;
        }
        else
        {
            chim_at_level [i] = list_chim[gioi_han_tren] ;
        }
    }





    TTF_Init() ;
    gfont = TTF_OpenFont("Xerox Sans Serif Wide Bold.ttf",28 );



    bool vao_game = false ;
    Base background ;

    Threat threat[so_luong_chim] ;
    //threat[0] = *new Threat ;threat[1] = *new Threat ;threat[2] = *new Threat ;
    for(int i = 0 ; i < so_luong_chim ; i ++)
        {
            if(i %2 == 0)
            {
                threat[i].set_vector_move(false) ;
                threat[i].setrect(1200 + i *random(100,400),random(20,100)) ;
            }
            else
            {
                threat[i].set_vector_move(true) ;
                threat[i].setrect(0 - i *random(100,400),random(20,100)) ;
            }

            threat[i].set_hp(20) ;

        }
    srand(time(NULL));

    init() ;
    background.setrect(0,0) ;
    human.setrect(600,423) ;
    bool quit = false, LorR = false ;

    /* loop */
    while(quit != true)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true ;
            }

            if(vao_game == true)
            {
                human.HandleAction(e) ;
                if(e.type != NULL)
                LorR = human.lorr(e) ;
                if(pause_game == false){
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y ;
                    SDL_GetMouseState(&x,&y) ;
                    {
                        if(1054 <= x && 1200 >= x && 0 <=y && 80 >=y)
                        {
                            pause_game = true ;
                        }
                    }

                }
                }
                else
                {
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x, y ;
                    SDL_GetMouseState(&x,&y) ;
                    {
                        if(400 <= x && 600>= x && 30 <=y && 80 >=y)
                        {
                            pause_game = false;
                        }
                        else if(400 <=x && 600 >=x &&200 <=y && 300 <=y  )
                        {
                            quit = true ;
                        }
                    }

                }
                }

            }
            // xu ly vao game hay khong
             if(  e.type == SDL_MOUSEBUTTONDOWN )
            {
                int x, y ;
                SDL_GetMouseState(&x,&y) ;
                if(500 <= x && 700 >= x && 50 <=y && 150 >=y)
                {
                    vao_game = true ;
                }
            }
        }
        human.HandleMove() ;

        if(vao_game == false)
        {
            background.loadfromfile("menu1-min.png");
            background.render() ;

        }
        if(vao_game){


        //clear screen
        SDL_SetRenderDrawColor( grenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( grenderer );

        //loadbackground

        background.loadfromfile("bg600-min.png") ;
        background.setrect(0,0) ;
        background.render() ;

        // pause game
        pause.loadfromfile("pause1.png") ;
        pause.setrect(1000,0) ;
        pause.render() ;

        // level ;
        text_level.Set_Color(1) ;
        text_level.Set_Text("LEVEL " + doi_so_sang_text(level)) ;
        text_level.setrect(20,20) ;
        text_level.loadFromRenderedText() ;
        text_level.render() ;

        if(pause_game)
        {
            background.loadfromfile("menu_pause.png");
            background.setrect(400,30) ;
            background.render() ;
        }
        else{


        //loadnhanvat
        if(LorR == true )
        {
            human.loadfromfile("guy.png");

        }
        else
        {
            human.loadfromfile("guy_flip.png");

        }
        //cout << LorR << endl ;
        human.render() ;

        for(int i = 0 ; i < so_luong_chim; i ++)
        {
            threat[i].loadfromfile(chim_at_level[i]) ;
            threat[i].threat_move() ;
            threat[i].render() ;


        for(int j = 0 ; j < threat[i].Bul.size() ; j ++ )
        {
            threat[i].Bul[j].loadfromfile("egg.png") ;
            if(threat[i].Bul[j].da_lay_muctieu == false)
            {

              threat[i].Bul[j].get_muctieu(human.get_pos_x(),human.get_pos_y());
              threat[i].Bul[j].SetVel((human.get_pos_x()- threat[i].Bul[j].get_pos_x())/absd(human.get_pos_x() -  threat[i].Bul[j].get_pos_x())*5 , (human.get_pos_y() -  threat[i].Bul[j].get_pos_y())/absd(human.get_pos_x()-threat[i].Bul[j].get_pos_x())*5) ;
              threat[i].Bul[j].da_lay_muctieu = true ;


            }
            threat[i].Bul[j].BulletMove() ;

            threat[i].Bul[j].render() ;
            if(CheckCollision1(human,threat[i].Bul[j]) == true || threat[i].Bul[j].get_move() == false)
            {
                threat[i].Bul.erase(threat[i].Bul.begin() + j ) ;

            }

        }


        }
            for(int k = 0 ; k < human.Bul.size() ; k++)
        {

            human.Bul[k].loadfromfile("sphere.png") ;
            human.Bul[k].set_up_or_down(true);
            human.Bul[k].BulletMove();
            human.Bul[k].set_hp(10) ;
            if(human.Bul[k].get_move())
            human.Bul[k].render() ;
            for(int i = 0 ; i < so_luong_chim ; i ++ ){
            if (CheckCollision(threat[i],human.Bul[k]))
            {
                //cout << "da va cham" << endl ;
                human.Bul.erase(human.Bul.begin() + k ) ;
                threat[i].hp -= human.Bul[k].hp ;
                if(threat[i].hp == 0)
                {

                    threat[i].hp = 20 ;
                    if(threat[i].get_vector() == false )
                    threat[i].setrect(3000,random(20,100)) ;
                    else threat[i].setrect(-1800,random(20,100)) ;
                    task -- ;
                }

            }
            }

            if(!human.Bul[k].get_move())
            {
                 human.Bul.erase(human.Bul.begin() + k ) ;
                 //cout << "daxoa va conlai "<< human.Bul.size() << endl ;
            }


        }


        // show score ;
        text_hp.Set_Color(1) ;
        text_hp.Set_Text("HP " + doi_so_sang_text(human.hp)) ;
        text_hp.setrect(20,60) ;
        text_hp.loadFromRenderedText() ;
        text_hp.render() ;

        text_task.Set_Color(1) ;
        text_task.Set_Text("TASK REMAIN " + doi_so_sang_text(task)) ;
        text_task.setrect(20,90) ;
        text_task.loadFromRenderedText() ;
        text_task.render() ;
        }
        }
       //render
        SDL_RenderPresent( grenderer );
    }
    close() ;
    op << level ;

    ifstream ip1 ("du_lieu_game1.txt") ;
    ofstream op1 ("du_lieu_game.txt") ;
    //level ++ ;
    ip1 >> level ;
    op1 << level ;
    return 0  ;
}
