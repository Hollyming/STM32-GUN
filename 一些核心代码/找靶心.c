/*****************寻找胸环靶中心*****************************/
void Image_FindCenter(int *CenterX,int *CenterY,int *cankaoX,int *cankaoY)
{
  int x,y;
  u8 res=15;
  //*CenterX=x;
  //*CenterY=y;
  //*cankaoX=x;
  //*cankaoY=y;  

  for(x=0;x<180;x++)
    for(y=90; y<150; y++)
    {
      if(Image_buffer[x][y]<=res)   //Image_buffer是240*240的数组
      {         
        if(Image_buffer[x+1][y+1]<=res)
		   if((Image_buffer[x][y+1]<=res)&&(Image_buffer[x+2][y+1]<=res)&&(Image_buffer[x+1][y]<=res)&&(Image_buffer[x+1][y+2]<=res))
				  //Image_buffer[x+1][y+1]的上下左右也都小于res
		   {
		      //res = Image_buffer[x+1][y+1];
			  if(x<40)
			  {
			    *cankaoX=x+2;
				*cankaoY=y+2;
			  }
			  else
			  {
		        *CenterX=x+2;
			    *CenterY=y+2;
			  }
		   }
      }
    }
}

/*****************寻找激光打靶的位置*****************************/
void Image_FindLight(int *LightX,int *LightY)
{
   int x=0,y=0;
   u8 res=40;
   *LightX=x;
   *LightY=y;

   for(x=0;x<240;x++)
    for(y=0;y<240; y++)
    {
      if(Image_buffer[x][y]>=res)
      {     
	     if(Image_buffer[x+1][y+1]>=res)    
            if((Image_buffer[x][y+1]>=res)&&(Image_buffer[x+2][y+1]>=res)&&(Image_buffer[x+1][y]>=res)&&(Image_buffer[x+1][y+2]>=res))
			  {
		      res = Image_buffer[x+1][y+1];
		      *LightX=x+1;
			  *LightY=y+1;
		   	  }
      }
    }
}

void test_huanshu(int zhongdian_X,int zhongdian_Y,int xiaozheng_X,int xiaozheng_Y,int guangdian_X,int guangdian_Y)
{
   double B_X,B_Y,L_X,L_Y;
   double zc_bj1, zc_bj2, zc_bijiao;
   int ZX1,ZY1,CX1,CY1,LX1,LY1;
   ZX1 = zhongdian_X;
   ZY1 = zhongdian_Y;
   CX1 = xiaozheng_X;
   CY1 = xiaozheng_Y;
   LX1 = guangdian_X;
   LY1 = guangdian_Y;

   B_X = (ZX1-CX1);
   B_Y = (ZY1-CY1);
   L_X = (LX1-ZX1);
   L_Y = (LY1-ZY1);
   zc_bj1 =	sqrt((B_X*B_X)+(B_Y*B_Y));
   zc_bj2 =	sqrt((L_X*L_X)+(L_Y*L_Y));
   zc_bijiao = (zc_bj2/zc_bj1)*10;

   if(zc_bijiao<1.7)    huanshu = 10;	   
   else if(zc_bijiao<3.34) huanshu = 9;
   else if(zc_bijiao<=5.0)   huanshu = 8;
   else if(zc_bijiao<6.7)  huanshu = 7;
   else if(zc_bijiao<8.34) huanshu = 6;
   else if(zc_bijiao<=10.0)  huanshu = 5; 
   else  huanshu = 0;
   //jiaodu = abs(L_X);
   //jiaodu = abs(L_X)/zc_bj2;
   jiaodu = 57.296*(asin(L_X/zc_bj2));	  //57.296*
   if(L_Y>=0)
      {
		 if(-22.5<jiaodu && jiaodu<22.5)        
		    {fangwei = 1;} 	   //正右
		 else if(22.5<=jiaodu && jiaodu<67.5)	 
		    {fangwei = 8;} 	   //右下
		 else if(-67.5<=jiaodu && jiaodu<=-22.5)
		    {fangwei = 2;}     //右上
		 else if(67.5<=jiaodu && jiaodu<=90)	  
		    {fangwei = 7;} 	   //正下
		 else if(-90<=jiaodu && jiaodu<=-67.5)  
		    {fangwei = 3;}	   //正上
	  }
   else
      {
	   	 if(-22.5<jiaodu && jiaodu<22.5)        
		    {fangwei = 5;} 	   //正左
		 else if(22.5<=jiaodu && jiaodu<67.5)	  
		    {fangwei = 6;} 	   //左下
		 else if(-67.5<=jiaodu && jiaodu<=-22.5)
		    {fangwei = 4;}     //左上
		 else if(67.5<=jiaodu && jiaodu<90)	  
		    { fangwei = 7;} 	   //正下
		 else if(-90<=jiaodu && jiaodu<=-67.5)  
		    {fangwei = 3;}	   //正上
	  }
   if(guangdian_X==0  && guangdian_Y==0)  fangwei = 0;
}

void show_huanshu(int X_huan,int X_fang)
{
   switch(X_fang)
   {
    case 0:
	      LCD_Show_HZ(130,245,32,tuo,0);
	      LCD_Show_HZ(164,245,32,ba,0);
		  break;
    case 1:
	      LCD_Show_HZ(130,245,32,zheng,0);
	      LCD_Show_HZ(164,245,32,you,0);
		  break;
    case 2:
		  LCD_Show_HZ(130,245,32,you,0);
	      LCD_Show_HZ(164,245,32,shang,0);
		  break;
	case 3:
	      LCD_Show_HZ(130,245,32,zheng,0);
	      LCD_Show_HZ(164,245,32,shang,0);
		  break;
    case 4:
		  LCD_Show_HZ(130,245,32,zuo,0);
	      LCD_Show_HZ(164,245,32,shang,0);
		  break;
	case 5:
	      LCD_Show_HZ(130,245,32,zheng,0);
	      LCD_Show_HZ(164,245,32,zuo,0);
		  break;
    case 6:
		  LCD_Show_HZ(130,245,32,zuo,0);
	      LCD_Show_HZ(164,245,32,xia,0);
		  break;
	case 7:
	      LCD_Show_HZ(130,245,32,zheng,0);
	      LCD_Show_HZ(164,245,32,xia,0);
		  break;
    case 8:
		  LCD_Show_HZ(130,245,32,you,0);
	      LCD_Show_HZ(164,245,32,xia,0);
		  break;
   }
   switch(X_huan)
   {
    case 0:
	      LCD_Show_HZ(130,280,32,tuo,0);
	      LCD_Show_HZ(164,280,32,ba,0);
		  break;
	case 5:
	      LCD_Show_HZ(130,280,32,WU5,0);
	      LCD_Show_HZ(164,280,32,huan,0);
		  break;
    case 6:
		  LCD_Show_HZ(130,280,32,LIU6,0);
	      LCD_Show_HZ(164,280,32,huan,0);
		  break;
	case 7:
	      LCD_Show_HZ(130,280,32,QI7,0);
	      LCD_Show_HZ(164,280,32,huan,0);
		  break;
    case 8:
		  LCD_Show_HZ(130,280,32,BA8,0);
	      LCD_Show_HZ(164,280,32,huan,0);
		  break;
	case 9:
	      LCD_Show_HZ(130,280,32,JIU9,0);
	      LCD_Show_HZ(164,280,32,huan,0);
		  break;
    case 10:
		  LCD_Show_HZ(130,280,32,SHI10,0);
	      LCD_Show_HZ(164,280,32,huan,0);
		  break;
   }

}
