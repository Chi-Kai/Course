function TiMu(){
	for(var i in data1){
		var div = document.createElement("div");
		div.className = "entrance-bottom-frame-line";
		document.querySelector(".entrance-bottom-frame").appendChild(div);
		
		var beijing = document.createElement("div");
		beijing.className = "entrance-bottom-frame-beijing";
		document.querySelectorAll(".entrance-bottom-frame-line")[i].appendChild(beijing);
		
		var div1 = document.createElement("div");
		div1.className = "entrance-bottom-frame-line-id";
		div1.innerHTML = data1[i].id;
		document.querySelectorAll(".entrance-bottom-frame-line")[i].appendChild(div1);
		
		var div2 = document.createElement("div");
		div2.className = "entrance-bottom-frame-line-title";
		div2.innerHTML = data1[i].title;
		document.querySelectorAll(".entrance-bottom-frame-line")[i].appendChild(div2);
		
		var code = document.createElement("code");
		var pre = document.createElement("pre");
		code.innerHTML = data1[i].code;
		pre.appendChild(code);
		pre.className = "pre_message"
		document.querySelectorAll(".entrance-bottom-frame-line")[i].appendChild(pre);
		
		for(var j in data1[i].xuanxiang){
			var div3 = document.createElement("div");
			div3.className = "entrance-bottom-frame-line-button";
			var div3_id = document.createElement("div");
			div3_id.className = "entrance-bottom-frame-line-button-id";
			if(j == 0){
				 div3_id.innerHTML = "A";
			}else if(j == 1){
				 div3_id.innerHTML = "B";
			}else if(j == 2){
				 div3_id.innerHTML = "C";
			}else{
				 div3_id.innerHTML = "D";
			}
			var div4 = document.createElement("div");
			div4.className = "entrance-bottom-frame-line-button-frame";
			div4.innerHTML = data1[i].xuanxiang[j];
			div3.appendChild(div3_id)
			div3.appendChild(div4);
			document.querySelectorAll(".entrance-bottom-frame-line")[i].appendChild(div3);
		}
	}
	
}

function addClass(obj, cls){
  var obj_class = obj.className,//获取 class 内容.
  blank = (obj_class != '') ? ' ' : '';//判断获取到的 class 是否为空, 如果不为空在前面加个'空格'.
  added = obj_class + blank + cls;//组合原来的 class 和需要添加的 class.
  obj.className = added;//替换原来的 class.
}

function removeClass(obj, cls){
  var obj_class = ' '+obj.className+' ';//获取 class 内容, 并在首尾各加一个空格. ex) 'abc    bcd' -> ' abc    bcd '
  obj_class = obj_class.replace(/(\s+)/gi, ' '),//将多余的空字符替换成一个空格. ex) ' abc    bcd ' -> ' abc bcd '
  removed = obj_class.replace(' '+cls+' ', ' ');//在原来的 class 替换掉首尾加了空格的 class. ex) ' abc bcd ' -> 'bcd '
  removed = removed.replace(/(^\s+)|(\s+$)/g, '');//去掉首尾空格. ex) 'bcd ' -> 'bcd'
  obj.className = removed;//替换原来的 class.
}

function hasClass(obj, cls){
  var obj_class = obj.className,//获取 class 内容.
  obj_class_lst = obj_class.split(/\s+/);//通过split空字符将cls转换成数组.
  x = 0;
  for(x in obj_class_lst) {
    if(obj_class_lst[x] == cls) {//循环数组, 判断是否包含cls
      return true;
    }
  }
  return false;
}


function getStyle(obj,attr){ 
  if(obj.currentStyle){ 
    return obj.currentStyle[attr]; 
  } 
  else{ 
    return document.defaultView.getComputedStyle(obj,null)[attr]; 
  } 
}

function CountDown() {
       minutes = Math.floor(mintime / 60);
      seconds = Math.floor(mintime % 60);
      if(minutes < 10){
      	minutes1 = "0" + minutes
       }else{
       	minutes1 = minutes
       }
       if(seconds < 10){
       	seconds1 = "0" + seconds
       }else{
       	seconds1 = seconds
       }
       msg =   minutes1 + ":" + seconds1;
     document.all["timer"].innerHTML = msg;
      if (maxtime == 5 * 60)alert("还剩5分钟");
          ++mintime;

       clearInterval(timer);

}

window.onload = function(){
	TiMu()
	mintime = 1; 
  timer = setInterval("CountDown()", 1000); 
	var dact = document.querySelector(".entrance-bottom-frame-line")
	var active = "active"
	var none = "none"
	addClass(dact, active)
	var timu_id = 0
	for(var i = 0;i<document.querySelectorAll(".entrance-bottom-frame-line-button").length;i++){
		document.querySelectorAll(".entrance-bottom-frame-line-button")[i].onclick = function(){
			if(timu_id < document.querySelectorAll(".entrance-bottom-frame-line").length - 1){
				var frame_left = getStyle(document.querySelector(".entrance-bottom-frame"),'marginLeft')
				document.querySelector(".entrance-bottom-frame").style.marginLeft = parseInt(frame_left) -1050 + "px"
				timu_id++;
				addClass(document.querySelectorAll(".entrance-bottom-frame-line")[timu_id], active)
				removeClass(document.querySelectorAll(".entrance-bottom-frame-line")[timu_id-1], active)
				addClass(document.querySelectorAll(".entrance-bottom-frame-beijing")[timu_id-1],none)
			}else{
				alert("最后一题啦")
				
			}
		}
	}
}


var data1 =[ {
             "id" : "1",  
             "title": "下列选项中不属于声音的重要指标的是（）",  
             "code": "A.频率"+ "<br>" + 
 	"B.音色"+ "<br>" +
    "C.周期 "+ "<br>" + 
	"D.振幅 "+ "<br>" 
	,			
             "xuanxiang":[
             				"频率",
             				"音色",
             				"周期",
             				"振幅",
             				]
	
        },{  
             "id" : "2",  
             "title": "自然界的声音是信号，要使计算机能处理音频信号必须将其--，这种准换过程即声音的数字化。",  
             "code":
				 	"&nbsp&nbsp"+"A.连续变化的模拟离散化"+ "<br>" +
				    "&nbsp&nbsp"+"B.离散变化的模拟离散化"+ "<br>" + 
					"&nbsp&nbsp"+"C.连续变化的数字离散化"+ "<br>" + 
					"&nbsp&nbsp"+"D.离散变化的数字连续化 "+ "<br>",	
             "xuanxiang":[
             				"连续变化的模拟离散化",
             				"离散变化的模拟离散化",
             				"连续变化的数字离散化",
             				"离散变化的数字连续化",
             				]
        },{  
             "id" : "3",  
             "title": "下列不属于波形编码器的是",  
             "code": 
					 	"&nbsp&nbsp"+"A.脉冲编码调制"+ "<br>" +
					    "&nbsp&nbsp"+"B.自适应差分编码"+ "<br>" + 
						"&nbsp&nbsp"+"C.自适应增量调制"+ "<br>" + 
						"&nbsp&nbsp"+"D.线性预测编码"+ "<br>" 
						,
             "xuanxiang":[
             				"脉冲编码调制",
             				"自适应差分编码",
             				"自适应增量调制",
             				"线性预测编码",
             				]
        },{  
             "id" : "4",  
             "title": "CMYK颜色模型中的“K”代表：",  
             "code": 
					 	"&nbsp&nbsp"+"A.紫色" +"<br>"+
					    "&nbsp&nbsp"+"B.蓝色"+ "<br>" + 
						"&nbsp&nbsp"+"C.黑色"+ "<br>" + 
						"&nbsp&nbsp"+"D.青色"+ "<br>",
             "xuanxiang":[
             				"紫色",
             				"蓝色",
             				"黑色",
             				"青色",
             				]
        },{  
             "id" : "5",  
             "title": "下列不属于多媒体技术的研究内容的是：",  
             "code": 
					 	"&nbsp&nbsp"+"A.图像处理"+ "<br>" +
					    "&nbsp&nbsp"+"B.质量服务"+ "<br>" + 
						"&nbsp&nbsp"+"C.用户界面"+ "<br>" + 
						"&nbsp&nbsp"+"D.软件工程"+ "<br>" ,
             "xuanxiang":[
             				"图像处理",
             				"质量服务",
             				"用户界面",
             				"软件工程",
             				]
        }
        ];
        

