package com.warehouse.news.homefragment.newslist;

import androidx.lifecycle.ViewModel;
import androidx.lifecycle.ViewModelProvider;

import com.warehouse.base.customview.BaseCustomViewModel;
import com.warehouse.base.mvvm.viewmodel.BaseMvvmListViewModel;

public class NewsListViewModel extends BaseMvvmListViewModel<NewsListModel, BaseCustomViewModel> {
    private String mChannelId;
    private String mChannelName;

    public static class NewsListViewModelFactory implements ViewModelProvider.Factory {
        private String mChannelId;
        private String mChannelName;
        public NewsListViewModelFactory(String channelId, String channelName) {
            this.mChannelId = channelId;
            this.mChannelName = channelName;
        }

        @Override
        public <T extends ViewModel> T create(Class<T> modelClass) {
            return (T) new NewsListViewModel(mChannelId, mChannelName);
        }
    }

    public NewsListViewModel(String channelId, String channelName){
        mChannelId= channelId;
        mChannelName = channelName;
    }

    @Override
    public NewsListModel createModel() {
        return new NewsListModel(mChannelId, mChannelName);
    }
}
