/*
    Copyright (c) 2012, Philipp Krähenbühl
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the Stanford University nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Philipp Krähenbühl ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Philipp Krähenbühl BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
//Saliency filters: Contrast based filtering for salient region detection
#include "saliency/saliency.h"
#include <cstdio>a
using namespace  std;;

void ComputerSaliency(Mat& src, Mat& saliencyImage, Mat& dst);

int main( int argc, char * argv[] ) {
	//if (argc < 2) {
	//	printf("Usage: %s image\n", argv[0] );
	//	return -1;
	//}
	//Mat im = imread( "G:\\Picture\\OFD_full_DB_labelled\\0001\\I_0001_05.jpg",1/*argv[1]*/ );
	//Saliency saliency;
	//Mat_<float> sal = saliency.saliency( im );
	//
	//double adaptive_T = 2.0 * sum( sal )[0] / (sal.cols*sal.rows);
	//while (sum( sal > adaptive_T )[0] == 0)
	//	adaptive_T /= 1.2;
	//imshow( "im", im );
	//imshow( "sal", sal );
	//imshow( "T", sal > adaptive_T );
	//waitKey();

	Directory dir;
	vector<string> imagePaths;
	//string dirPath="G:\\Picture\\PEL2";
	//string dirPath="G:\\Picture\\three";
	string dirPath="G:\\Picture\\yaleB_three_class_crop\\test\\2";
	imagePaths = dir.GetListFilesR(dirPath);
	for(int i=0;i<100/*imagePaths.size()*/;i++)
	{
		Mat src=imread(imagePaths[i],1);
		//resize(src,src,Size(200,200));
		Mat saliencyImage;
		Mat temp;
		Mat dst;
		Mat dst1;
		ComputerSaliency(src,saliencyImage,temp);
		temp.convertTo(temp,CV_32F);
		//for(int i=0;i<temp.rows;i++)
		//{
		//	for (int j=0;j<temp.cols;j++)
		//	{
		//		cout<<temp.at<float>(i,j)<<" ";
		//	}
		//	cout<<endl;
		//}
			
		cvtColor(src,src,CV_BGR2GRAY);
		src.convertTo(src,CV_32F);
		dst=src-temp;
		temp=255.0-temp;
		dst1=src-temp;
		src.convertTo(src,CV_8U);
		dst.convertTo(dst,CV_8U);
		dst1.convertTo(dst1,CV_8U);
		equalizeHist(src,src);
		equalizeHist(dst,dst);
		equalizeHist(dst1,dst1);
		dst1=dst1+dst;
		imshow( "im", src ); 
		imshow( "sal", saliencyImage );
		imshow( "dst", dst); 
		imshow( "dst1", dst1 ); 
		waitKey(0);
	}
	
	return 0;
}

void ComputerSaliency(Mat& src, Mat& saliencyImage, Mat& dst)
{
	Saliency saliency;
	Mat_<float> sal = saliency.saliency( src );

	double adaptive_T = 2.0 * sum( sal )[0] / (sal.cols*sal.rows);
	while (sum( sal > adaptive_T )[0] == 0)
		adaptive_T /= 1.2;
	saliencyImage=sal;
	dst=sal > adaptive_T;
}