#include <stdio.h>
 
// ÇòÔ±
class Player
{
public:
       Player(char* _name) : name(_name){}
      
       virtual void Attack()=0;
       virtual void Defense()=0;
 
       char* name;
};
 
// Ç°·æ
class Forwards : public Player
{
public:
       Forwards(char* name) : Player(name){}
      
       virtual void Attack()
       {
              printf("Ç°·æ %s ½ø¹¥\n", name);
       }
      
       virtual void Defense()
       {
              printf("Ç°·æ %s ·ÀÊØ\n", name);
       }
};
 
// ÖĞ·æ
class Center : public Player
{
public:
       Center(char* name) : Player(name){}
      
       virtual void Attack()
       {
              printf("ÖĞ·æ %s ½ø¹¥\n", name);
       }
      
       virtual void Defense()
       {
              printf("ÖĞ·æ %s ·ÀÊØ\n", name);
       }
};
 
// ºóÎÀ
class Guards : public Player
{
public:
       Guards(char* name) : Player(name){}
      
       virtual void Attack()
       {
              printf("ºóÎÀ %s ½ø¹¥\n", name);
       }
      
       virtual void Defense()
       {
              printf("ºóÎÀ %s ·ÀÊØ\n", name);
       }
};
 
// Íâ¼®ÖĞ·æ
class ForeignCenter
{
public:
       void Attack()
       {
              printf("Íâ¼®ÖĞ·æ %s ½ø¹¥\n", name);
       }
      
       void Defense()
       {
              printf("Íâ¼®ÖĞ·æ %s ·ÀÊØ\n", name);
       }
      
       char* name;
};
 
// ·­ÒëÕß
class Translator : public Player
//class Translator 
{
public:
       Translator(char* name) : Player(name)
       //Translator(char* name) 
       {
              wjzf.name = name;
       }
      
       virtual void Attack()
       {
              wjzf.Attack();
       }
      
       virtual void Defense()
       {
              wjzf.Defense();
       }
protected:
       ForeignCenter wjzf;
};
 
int main()
{
       Player* b = new Forwards("°ÍµÙ¶û");
       b->Attack();
      
       Player* m = new Guards("Âó¿Ë¸ñÀ×µÏ");
       m->Attack();
      
       Player* ym = new Translator("Ò¦Ã÷");
       //Translator* ym = new Translator("Ò¦Ã÷");
       ym->Attack();
       ym->Defense();
      
       delete b;
       delete m;
       delete ym;
      
       return 0;
}


