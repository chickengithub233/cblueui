
//幻灯片演示
function show_demo_all_page() {
	var btn = ControlObj("macdeskui"); 

	//基本控件
	btn.ShellAttribute("cursel", 0);
	var contain = ControlObj("tab-1"); 
	for (var i = 0; i < 50; i+= 5) {
		contain.ShellAttribute("vscroll-pos-percent", i);
		sleep(100);
	}

	sleep(1000);
	var slider = ControlObj("silderctl"); 
	for (var i = 50; i >= 20; i-= 5) {
		slider.ShellAttribute("value", i);
		sleep(100);
	}

	//表格
	btn.ShellAttribute("cursel", 1);
	sleep(1000);
	var contain = ControlObj("tabMusiclist"); 
	contain.ShellAttribute("vscroll-pos-percent", 0);
	for (var i = 0; i < 50; i+= 5) {
		contain.ShellAttribute("vscroll-pos-percent", i);
		sleep(100);
	}
	sleep(1000);

	
	//树
	btn.ShellAttribute("cursel", 2);
	var contain = ControlObj("treetable"); 
	contain.ShellAttribute("vscroll-pos-percent", 0);
	for (var i = 0; i < 50; i+= 5) {
		contain.ShellAttribute("hscroll-pos-percent", i);
		sleep(100);
	}
	sleep(1000);
	contain.ShellAttribute("vscroll-pos-percent", 0);
	for (var i = 10; i < 60; i+= 5) {
		contain.ShellAttribute("vscroll-pos-percent", i);
		sleep(100);
	}
	sleep(1000);

	
	btn.ShellAttribute("cursel", 3);
	sleep(1000);


	
	btn.ShellAttribute("cursel", 4);
	sleep(1000);


	//
	btn.ShellAttribute("cursel", 5);
	var arr = ['btnchar01','btnchar02','btnchar03','btnchar04','btnchar04','btnchar05','btnchar06','btnchar07','btnchar08','btnchar09','btnchar10','btnchar11','btnchar12'];
	for(var i=0;i<arr.length;i++) {
		var btn_tab = ControlObj(arr[i]); 
		btn_tab.ShellAttribute("click", 0);
		sleep(1500);
	}
	sleep(1000);

	//
	btn.ShellAttribute("cursel", 6);
	sleep(1000);

	
	btn.ShellAttribute("cursel", 7);
	sleep(1000);

	
	btn.ShellAttribute("cursel", 8);
	sleep(1000);

	
	btn.ShellAttribute("cursel", 9);
	var contain = ControlObj("tab-10"); 
	contain.ShellAttribute("vscroll-pos-percent", 50);
	sleep(1000);

	
	btn.ShellAttribute("cursel", 10);
	sleep(1000);

	btn.ShellAttribute("cursel", 11);
	var contain = ControlObj("sync_scroll"); 
	contain.ShellAttribute("vscroll-pos-percent", 0);
	for (var i = 10; i < 100; i+= 5) {
		contain.ShellAttribute("vscroll-pos-percent", i);
		sleep(100);
	}
	sleep(1000);

	
	btn.ShellAttribute("cursel", 12);
	sleep(1000);

	
	btn.ShellAttribute("cursel", 13);
	sleep(1000);

	
	// btn.ShellAttribute("cursel", 14);
	// sleep(1000);

	
}


//语言切换测试
var combo_switch_lang = ControlObj("switch_lang"); 
var combo_theme = ControlObj("input_theme"); 

//基本控件
var btn = ControlObj("macdeskui"); 
btn.ShellAttribute("cursel", 0);
sleep(1000);
btn.ShellAttribute("cursel", 2);
for (var i = 1; i < 9; i+= 1) {
	sleep(1000);
	combo_switch_lang.ShellAttribute("cursel", i%8);
}


// 布局翻转
var btnLayoutReverse = ControlObj("btnLayoutReverse"); 
btnLayoutReverse.ShellAttribute("click", 0);
sleep(1000);
btnLayoutReverse.ShellAttribute("click", 0);
sleep(1000);

var themeNo = 0;
combo_theme.ShellAttribute("cursel", (++themeNo)%2);
sleep(2000);
btn.ShellAttribute("cursel", 0);
sleep(1000);
combo_theme.ShellAttribute("cursel", (++themeNo)%2);
sleep(1000);

show_demo_all_page();



