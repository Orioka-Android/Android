package com.example.drawerlayoutsample1;

import android.app.Activity;
import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v7.app.ActionBarDrawerToggle;
import android.view.MenuItem;
import android.view.View;
import android.widget.ListView;


public class DrawerLayout extends Activity{

	private Activity activity;
	protected void onCreate(Bundle savedInstanceState) {
	    super.onCreate(savedInstanceState);
	    setContentView(R.layout.slide_menu);
	    setSlideMenu();





	}




	/**
	 * サイドメニューに登録したListViewを編集します。
	 *@author 凜太郎
	 */
	private void slideMenuListView() {
		ListView listView = (ListView)findViewById(R.id.listViewSlideMenu);
		//ListViewの処理を追加してください。

	}

	private ActionBarDrawerToggle actionBarDrawerToggle;
	android.support.v4.widget.DrawerLayout drawerLayout;
	/**
	 * サイドメニュー（DrawerLayout)が動くのに必要な処理です。
	 * テーマをいじったりしています。
	 * @author 凜太郎
	 */
	private void setSlideMenu(){
		drawerLayout = (android.support.v4.widget.DrawerLayout) findViewById(R.id.drawer_layout);
	    actionBarDrawerToggle = new ActionBarDrawerToggle(this, drawerLayout, R.drawable.abc_ab_share_pack_holo_light, 0) {
	        @Override
	        public void onDrawerClosed(View drawerView) {
	        }
	        @Override
	        public void onDrawerOpened(View drawerView) {
	        }
	        @Override
	        public void onDrawerSlide(View drawerView, float slideOffset) {
	            // ActionBarDrawerToggleクラス内の同メソッドにてアイコンのアニメーションの処理をしている。
	            // overrideするときは気を付けること。
	            super.onDrawerSlide(drawerView, slideOffset);
	        }
	        @Override
	        public void onDrawerStateChanged(int newState) {
	            // 表示済み、閉じ済みの状態：0
	            // ドラッグ中状態:1
	            // ドラッグを放した後のアニメーション中：2
	        }
	    };

	    drawerLayout.setDrawerListener(actionBarDrawerToggle);

	    // UpNavigationアイコン(アイコン横の<の部分)を有効に
	    // NavigationDrawerではR.drawable.drawerで上書き
	    getActionBar().setDisplayHomeAsUpEnabled(true);
	    // UpNavigationを有効に
	    getActionBar().setHomeButtonEnabled(true);

	}

	@Override
	protected void onPostCreate(Bundle savedInstanceState) {
	    super.onPostCreate(savedInstanceState);
	    actionBarDrawerToggle.syncState();
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
	    super.onConfigurationChanged(newConfig);
	    actionBarDrawerToggle.onConfigurationChanged(newConfig);
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
	    // ActionBarDrawerToggleにandroid.id.home(up ナビゲーション)を渡す。
	    if (actionBarDrawerToggle.onOptionsItemSelected(item)) {
	        return true;
	    }

	    return super.onOptionsItemSelected(item);
	}

}
