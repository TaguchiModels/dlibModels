/*
  Written by Taguchi.
   The original source code is "dnn_imagenet_ex.cpp" in the dlib example folder.
   This source code has been modified to use "taguchi_model_gender_classifier.dnn" instead of using 
   "resnet34_1000_imagenet_classifier.dnn".

     Example) GenderModelClassifier gender
*/



#include <dlib/dnn.h>
#include <iostream>
#include <dlib/data_io.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_transforms.h>

using namespace std;
using namespace dlib;

// ----------------------------------------------------------------------------------------

// This block of statements defines the resnet-34 network

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET> using alevel1 = ares<512, ares<512, ares_down<512, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<256, ares<256, ares<256, ares<256, ares<256, ares_down<256, SUBNET>>>>>>;
template <typename SUBNET> using alevel3 = ares<128, ares<128, ares<128, ares_down<128, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<64, ares<64, ares<64, SUBNET>>>;

using anet_type = loss_multiclass_log <fc<2, avg_pool_everything<
	alevel1<
	alevel2<
	alevel3<
	alevel4<
	max_pool<3, 3, 2, 2, relu<affine<con<64, 7, 7, 2, 2,
	input_rgb_image_sized<150>
	>>>>>>>>>>>;

// ----------------------------------------------------------------------------------------

rectangle make_random_cropping_rect_resnet(
	const matrix<rgb_pixel>& img,
	dlib::rand& rnd
)
{
	// figure out what rectangle we want to crop from the image
	double mins = 0.466666666, maxs = 0.875;
	auto scale = mins + rnd.get_random_double()*(maxs - mins);
	auto size = scale * std::min(img.nr(), img.nc());
	rectangle rect(size, size);
	// randomly shift the box around
	point offset(rnd.get_random_32bit_number() % (img.nc() - rect.width()),
		rnd.get_random_32bit_number() % (img.nr() - rect.height()));
	return move_rect(rect, offset);
}

// ----------------------------------------------------------------------------------------

void randomly_crop_images(
	const matrix<rgb_pixel>& img,
	dlib::array<matrix<rgb_pixel>>& crops,
	dlib::rand& rnd,
	long num_crops
)
{
	std::vector<chip_details> dets;
	for (long i = 0; i < num_crops; ++i)
	{
		auto rect = make_random_cropping_rect_resnet(img, rnd);
		dets.push_back(chip_details(rect, chip_dims(150, 150)));
	}

	extract_image_chips(img, dets, crops);

	for (auto&& img : crops)
	{
		// Also randomly flip the image
		if (rnd.get_random_double() > 0.5)
			img = fliplr(img);

		// And then randomly adjust the colors.
		apply_random_color_offset(img, rnd);
	}
}

// ----------------------------------------------------------------------------------------

int main(int argc, char** argv) try
{
	if (argc == 1)
	{
		cout << "Give this program image files as command line arguments.\n" << endl;
		cout << "You will also need a copy of the file taguchi_gender_classifier.dnn " << endl;
		cout << endl;
		return 1;
	}

	std::vector<string> labels;
	anet_type net;
	labels.push_back("female");
	labels.push_back("male");
	cout << " deserialize start " << endl;
	//deserialize("resnet34.dnn") >> net >> labels;
	deserialize("taguchi_model_gender_classifier.dnn") >> net;
	cout << " deserialize end " << endl;

	// Make a network with softmax as the final layer.  We don't have to do this
	// if we just want to output the single best prediction, since the anet_type
	// already does this.  But if we instead want to get the probability of each
	// class as output we need to replace the last layer of the network with a
	// softmax layer, which we do as follows:
	softmax<anet_type::subnet_type> snet;
	snet.subnet() = net.subnet();

	dlib::array<matrix<rgb_pixel>> images;
	matrix<rgb_pixel> img, crop;

	dlib::rand rnd;
	image_window win;

	// Load test images.
	auto dir = directory(argv[1]);
	for (auto image_file : dir.get_files())
	{
		load_image(img, image_file);
		const int num_crops = 16;
		randomly_crop_images(img, images, rnd, num_crops);
		matrix<float, 1, 2> p = sum_rows(mat(snet(images.begin(), images.end()))) / num_crops;

		win.set_image(img);
		unsigned long predicted_label = index_of_max(p);
		cout << "file:"  << image_file << " " << p(predicted_label) << ": " << labels[predicted_label] << endl;
	}

}
catch (std::exception& e)
{
	cout << e.what() << endl;
}

