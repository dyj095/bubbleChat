# bubbleChat
QProgressBar样式表(原文：https://blog.csdn.net/cliffordl/article/details/42063561 )

## 第一步：<br>
       (<br>
       "height:30;"<br>
       "background: red;"<br>
       "color:rgb(255,255,0);"<br>
       );<br>
       效果如下图：此时背景颜色没有起作用。<br>
              ![效果图1](https://img-blog.csdn.net/20141225132038809?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2xpZmZvcmRs/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

## 第二步：
       (<br>
      "border:1px solid #FFFFFF;"<br>
       "height:30;"<br>
       "background: red;"<br>
       "color:rgb(255,255,0);"<br>
       );<br>
        效果如下图：加上border之后，背景颜色变成红色，并且value出现在border里面。<br>        
              ![效果图2](https://img-blog.csdn.net/20141225132148557?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2xpZmZvcmRs/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)

## 第三步：

       (<br>
      "border:1px solid #FFFFFF;"<br>
      "height:30;"<br>
      "background: red;"<br>
      "text-align: center;"   // 控制文本位置left center right<br>
      "color:rgb(255,255,0);"<br>
       "border-radius:10px;"  // 圆角<br>
      );<br>
        效果如下图：<br>
              ![效果图3](https://img-blog.csdn.net/20141225132407640?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2xpZmZvcmRs/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)


 第四步：添加斑马线。
        ("QProgressBar{border:1px solid #FFFFFF;"

       "height:30;"

       "background:red;"

       "text-align:center;"

       "color:rgb(255,255,0);"

       "border-radius:10px;}"

       "QProgressBar::chunk{"

       "border-radius:5px;"    // 斑马线圆角

       "border:1px solid black;" // 黑边，默认无边

       "background-color:skyblue;"

       "width:8px;margin:0.5px;}" // 宽度和间距

       );

          效果如下图：
          
 ![效果图4](https://img-blog.csdn.net/20141225132925781?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2xpZmZvcmRs/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)


如果无border效果如下图。

 ![效果图5](https://img-blog.csdn.net/20141225133027429?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2xpZmZvcmRs/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)


第五步：

       ("QProgressBar::chunk{background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 red,stop:1 blue);}");

 ![效果图6](https://img-blog.csdn.net/20141225133351493?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvY2xpZmZvcmRs/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)
