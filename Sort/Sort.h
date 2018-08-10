#ifndef SORT_H
#define SORT_H

#include "Object/Object.h"
#include "Array/Array.h"

namespace ZYLib
{

#define MINORMAX(a,b,c) ((a) ? ((b) > (c)) : ((b) < (c)))

class Sort:public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator =(const Sort&);

    template <typename T>
    static void swap(T& a,T& b)
    {
        T c(a);
        a=b;
        b=c;
    }

    template <typename T>
    static void MergeDevide(T array[],T* helper,int begin,int end,bool min_to_max)
    {
        if(begin < end)
        {
            int mid=(begin+end)/2;
            MergeDevide(array,helper,begin,mid,min_to_max);
            MergeDevide(array,helper,mid+1,end,min_to_max);
            MergeSort(array,helper,begin,mid,end,min_to_max);
        }
    }

    template <typename T>
    static void MergeSort(T array[],T* helper,int begin,int mid,int end,bool min_to_max)
    {
        int i=begin;
        int j=mid+1;
        int k=begin;
        while(i<=mid && j<=end)
        {
            if(MINORMAX(min_to_max,array[i],array[j]))
            {
                helper[k++]=array[j++];
            }
            else
            {
                helper[k++]=array[i++];
            }
        }

        while(i<=mid)
            helper[k++]=array[i++];

        while(j<=end)
            helper[k++]=array[j++];

        for(int i=begin;i<k;i++)
            array[i]=helper[i];
    }

    template <typename T>
    static int Partition(T array[],int begin,int end,bool min_to_max)
    {
        //T pv=array[begin];
        while(begin < end)
        {
            while(begin < end && MINORMAX(min_to_max,array[end],array[begin]))
                end--;

            swap(array[begin],array[end]);

            while(begin < end && MINORMAX(min_to_max,array[end],array[begin]))
                begin++;

            swap(array[begin],array[end]);
        }
        //array[begin]=pv;
        return begin;
    }

    template <typename T>
    static void Quick(T array[],int begin,int end,bool min_to_max)
    {
        if(begin < end)
        {
            int pv=Partition(array,begin,end,min_to_max);
            Quick(array,begin,pv-1,min_to_max);
            Quick(array,pv+1,end,min_to_max);
        }
    }

public:
    template <typename T>
    static void print(T a[],int len)
    {
        for(int i=0;i<len;i++)
        {
            cout<<a[i]<<"  ";
        }
        cout<<endl;
    }

    template <typename T>
    static void Select(T array[],int len,bool min_to_max=true)
    {
        for(int i=0;i<len-1;i++)
        {
            int index=i;
            for(int j=i+1;j<len;j++)
            {
                if(MINORMAX(min_to_max,array[index],array[j]))
                {
                    index=j;
                }
            }

            if(index != i)
                swap(array[index],array[i]);
        }
    }

    template <typename T>
    static void Insert(T array[],int len,bool min_to_max=true)
    {
        for(int i=1;i<len;i++)
        {
            int k=i;
            T e=array[i];
            for(int j=i-1;j>=0 && (MINORMAX(min_to_max,array[j],e));j--)
            {
                array[j+1]=array[j];
                k=j;
            }
            if(k != i)
               array[k]=e;
        }
    }

    template <typename T>
    static void Bubble(T array[], int len, bool min_to_max=true)
    {
        for(int i=0;i<len;i++)
        {
            bool exchange=false;
            for(int j=len-1;j>i;j--)
            {
                if(MINORMAX(min_to_max,array[j-1],array[j]))
                {
                    exchange=true;
                    swap(array[j-1],array[j]);
                }
            }
            if(!exchange)   break;
        }
    }
    
    template <typename T>
    static void ShellMove(T array[], int len, bool min_to_max=true)
    {
        int d=len;
        while(d > 1)
        {
            d=d/3+1;

            for(int i=d;i<len;i++)
            {
                int k=i;
                T e=array[i];

                for(int j=i;j-d>=0 && MINORMAX(min_to_max,array[j-d],e);j-=d)
                {
                    array[j]=array[j-d];
                    k=j-d;
                }

                if(k != i)
                    array[k]=e;
            }
        }
    }

    template <typename T>
    static void ShellSwap(T array[], int len, bool min_to_max=true)
    {
        int d=len;
        while(d > 1)
        {
            d=d/3+1;

            for(int i=d;i<len;i++)
            {
                for(int j=i;j-d>=0 && MINORMAX(min_to_max,array[j-d],array[j]);j-=d)
                {
                    swap(array[j-d],array[j]);
                }
            }
        }
    }

    template <typename T>
    static void Merge(T array[],int len,bool min_to_max=true)
    {
        T* helper=new T[len];

        if(helper != NULL)
            MergeDevide(array,helper,0,len-1,min_to_max);

        delete[] helper;
    }

    template <typename T>
    static void Quick(T array[],int len,bool min_to_max=true)
    {
        Quick(array, 0, len-1, min_to_max);
    }


    //重载函数-支持对Array类对象排序
    template <typename T>
    static void print(Array<T>& arr)
    {
        print(arr.array(),arr.length());
    }

    template <typename T>
    static void Select(Array<T>& arr,bool flag=true)
    {
        Select(arr.array(),arr.length(),flag);
    }

    template <typename T>
    static void Insert(Array<T>& arr,bool flag=true)
    {
        Insert(arr.array(),arr.length(),flag);
    }

    template <typename T>
    static void Bubble(Array<T>& arr,bool flag=true)
    {
        Bubble(arr.array(),arr.length(),flag);
    }

    template <typename T>
    static void ShellMove(Array<T>& arr,bool flag=true)
    {
        ShellMove(arr.array(),arr.length(),flag);
    }

    template <typename T>
    static void ShellSwap(Array<T>& arr,bool flag=true)
    {
        ShellSwap(arr.array(),arr.length(),flag);
    }

    template <typename T>
    static void Merge(Array<T>& arr,bool flag=true)
    {
        Merge(arr.array(),arr.length(),flag);
    }

    template <typename T>
    static void Quick(Array<T>& arr,bool flag=true)
    {
        Quick(arr.array(),arr.length(),flag);
    }

};

}

#endif // SORT_H
