package com.ztiany.view.custom;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;

import com.ztiany.view.R;
import com.ztiany.view.custom.custom_viewgroup.SquareEnhanceLayout;
import com.ztiany.view.custom.custom_viewpager.HScrollLayoutBuilder;
import com.ztiany.view.custom.image.LargeImageView;
import com.ztiany.view.custom.image.LargeImageView2;
import com.ztiany.view.custom.image.ZoomImageView;
import com.ztiany.view.custom.ruler.RulerView;
import com.ztiany.view.custom.surfaceview.LoadingView;
import com.ztiany.view.custom.views.LockPatternView;
import com.ztiany.view.custom.views.Ring;
import com.ztiany.view.custom.views.SurfaceViewSinFun;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Ztiany
 * Email: ztiany3@gmail.com
 * Date : 2017-08-05 15:44
 */
public class CustomViewFragment extends Fragment {


    private List<View> mViewList = new ArrayList<>();
    private FrameLayout mFrameLayout;

    private String[] titles = {
            "水平滑动",
            "BitmapDecor显式大图",
            "BitmapDecor显式大图 + inBitmap内存复用",
            "Surface Loading",
            "宫格锁",
            "圆环",
            "尺子",
            "正方形布局",
            "可缩放的ImageView",
            "SurfaceViewSinFun"
    };

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mViewList.add(HScrollLayoutBuilder.buildHScrollLayout(getContext()));
        try {
            LargeImageView largeImageView = new LargeImageView(getContext());
            largeImageView.setImageStream(requireContext().getAssets().open("qm.jpg"));
            mViewList.add(largeImageView);
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            LargeImageView2 largeImageView2 = new LargeImageView2(getContext());
            largeImageView2.setImage(requireContext().getAssets().open("android.png"));
            mViewList.add(largeImageView2);
        } catch (IOException e) {
            e.printStackTrace();
        }
        mViewList.add(new LoadingView(getContext()));
        mViewList.add(new LockPatternView(getContext()));
        mViewList.add(new Ring(getContext(), null));
        mViewList.add(new RulerView(getContext()));
        mViewList.add(new SquareEnhanceLayout(getContext()));
        ZoomImageView imageView = new ZoomImageView(getContext());
        imageView.setImageResource(R.drawable.img_girl_01);
        mViewList.add(imageView);
        mViewList.add(new SurfaceViewSinFun(getContext()));
        setHasOptionsMenu(true);
    }


    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return mFrameLayout != null ? mFrameLayout : (mFrameLayout = new FrameLayout(requireContext()));
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        mFrameLayout.removeAllViews();
        mFrameLayout.addView(mViewList.get(0), new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        super.onCreateOptionsMenu(menu, inflater);
        MenuItem.OnMenuItemClickListener onMenuItemClickListener = new MenuItem.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                mFrameLayout.removeAllViews();
                mFrameLayout.addView(mViewList.get(item.getItemId()), new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
                return true;
            }
        };

        for (int i = 0; i < titles.length; i++) {
            menu.add(Menu.NONE, i, i, titles[i]).setOnMenuItemClickListener(onMenuItemClickListener);
        }
    }

}
