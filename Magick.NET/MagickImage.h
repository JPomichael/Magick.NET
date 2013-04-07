//=================================================================================================
// Copyright 2013 Dirk Lemstra <http://magick.codeplex.com/>
//
// Licensed under the ImageMagick License (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of the License at
//
//   http://www.imagemagick.org/script/license.php
//
// Unless required by applicable law or agreed to in writing, software distributed under the
// License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied. See the License for the specific language governing permissions and
// limitations under the License.
//=================================================================================================
#pragma once

#include "Colors\MagickColor.h"
#include "Drawables\DrawableAffine.h"
#include "Drawables\DrawableBase.h"
#include "Enums\Channels.h"
#include "Enums\ClassType.h"
#include "Enums\ColorSpace.h"
#include "Enums\ColorType.h"
#include "Enums\CompositeOperator.h"
#include "Enums\DistortMethod.h"
#include "Enums\Endian.h"
#include "Enums\FillRule.h"
#include "Enums\Gravity.h"
#include "Enums\ImageType.h"
#include "Enums\NoiseType.h"
#include "Enums\PaintMethod.h"
#include "Helpers\CompareResult.h"
#include "Helpers\MagickException.h"
#include "Helpers\MagickReader.h"
#include "Helpers\MagickWrapper.h"
#include "Helpers\MagickWriter.h"
#include "Helpers\TypeMetric.h"
#include "MagickBlob.h"
#include "MagickGeometry.h"
#include "Matrices\MatrixColor.h"
#include "Matrices\MatrixConvolve.h"

using namespace System::Collections::Generic;

namespace ImageMagick
{
	///=============================================================================================
	///<summary>
	/// Encapsulation of the ImageMagick image object.
	///</summary>
	public ref class MagickImage sealed : MagickWrapper<Magick::Image>
	{
		//===========================================================================================
	private:
		//===========================================================================================
		String^ _ReadWarning;
		//===========================================================================================
		MagickImage();
		//===========================================================================================
		String^ FormatedFileSize();
		//===========================================================================================
		void ReplaceImage(Magick::Image* image);
		//===========================================================================================
	internal:
		//===========================================================================================
		MagickImage(Magick::Image* image);
		//===========================================================================================
	public:
		///==========================================================================================
		///<summary>
		/// Initializes a new instance of the MagickImage class using the specified width, height
		/// and color.
		///</summary>
		///<param name="width">The width.</param>
		///<param name="height">The height.</param>
		///<param name="color">The color to fill the image with.</param>
		MagickImage(int width, int height, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Join images into a single multi-image file.
		///</summary>
		property bool Adjoin
		{
			bool get()
			{
				return Value->adjoin();
			}
			void set(bool value)
			{
				Value->adjoin(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Time in 1/100ths of a second which must expire before splaying the next image in an
		/// animated sequence.
		///</summary>
		property int AnimationDelay
		{
			int get()
			{
				return Value->animationDelay();
			}
			void set(int value)
			{
				Value->animationDelay(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Number of iterations to loop an animation (e.g. Netscape loop extension) for.
		///</summary>
		property int AnimationIterations
		{
			int get()
			{
				return Value->animationIterations();
			}
			void set(int value)
			{
				Value->animationIterations(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Anti-alias Postscript and TrueType fonts (default true).
		///</summary>
		property bool AntiAlias
		{
			bool get()
			{
				return Value->antiAlias();
			}
			void set(bool value)
			{
				Value->antiAlias(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Background color of the image.
		///</summary>
		property MagickColor^ Background
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->backgroundColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = value != nullptr ? value->CreateColor() : new Magick::Color();
				Value->backgroundColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Height of the image before transformations.
		///</summary>
		property int BaseHeight
		{
			int get()
			{
				return Value->baseRows();
			}
		}
		///==========================================================================================
		///<summary>
		/// Width of the image before transformations.
		///</summary>
		property int BaseWidth
		{
			int get()
			{
				return Value->baseColumns();
			}
		}
		///==========================================================================================
		///<summary>
		/// Return smallest bounding box enclosing non-border pixels. The current fuzz value is used
		/// when discriminating between pixels.
		///</summary>
		property MagickGeometry^ BoundingBox
		{
			MagickGeometry^ get()
			{
				return gcnew MagickGeometry(Value->boundingBox());
			}
		}
		///==========================================================================================
		///<summary>
		/// Image class (DirectClass or PseudoClass)
		/// NOTE: Setting a DirectClass image to PseudoClass will result in the loss of color information
		/// if the number of colors in the image is greater than the maximum palette size (either 256 (Q8)
		/// or 65536 (Q16).
		///</summary>
		property ClassType ClassType
		{
			ImageMagick::ClassType get()
			{
				return (ImageMagick::ClassType)Value->classType();
			}
			void set(ImageMagick::ClassType value)
			{
				return Value->classType((MagickCore::ClassType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Associate a clip mask with the image. The clip mask must be the same dimensions as the
		/// image. Pass null to unset an existing clip mask.
		///</summary>
		property MagickImage^ ClipMask
		{
			MagickImage^ get()
			{
				Magick::Image* image = new Magick::Image(Value->clipMask());
				return gcnew MagickImage(image);
			}
			void set(MagickImage^ value)
			{
				if (value == nullptr)
				{
					Magick::Image* image = new Magick::Image();
					Value->clipMask(*image);
					delete image;
				}
				else
				{
					Value->clipMask(*value->Value);
				}
			}
		}
		///==========================================================================================
		///<summary>
		/// Colors within this distance are considered equal.
		///</summary>
		property double ColorFuzz
		{
			double get()
			{
				return Value->colorFuzz();
			}
			Void set(double value)
			{
				Value->colorFuzz(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Colormap size (number of colormap entries).
		///</summary>
		property int ColorMapSize
		{
			int get()
			{
				return Value->colorMapSize();
			}
			void set(int value)
			{
				Value->colorMapSize(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Color space of the image.
		///</summary>
		property ColorSpace ColorSpace
		{
			ImageMagick::ColorSpace get()
			{
				return (ImageMagick::ColorSpace)Value->colorSpace();
			}
			void set(ImageMagick::ColorSpace value)
			{
				return Value->colorSpace((MagickCore::ColorspaceType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Color type of the image.
		///</summary>
		property ColorType ColorType
		{
			ImageMagick::ColorType get()
			{
				return (ImageMagick::ColorType)Value->type();
			}
			void set(ImageMagick::ColorType value)
			{
				return Value->type((MagickCore::ImageType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Comment text of the image.
		///</summary>
		property String^ Comment
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->comment());
			}
			void set(String^ value)
			{
				std::string comment; 
				Value->comment(Marshaller::Marshal(value, comment));
			}
		}
		///==========================================================================================
		///<summary>
		/// Vertical and horizontal resolution in pixels of the image.
		///</summary>
		property MagickGeometry^ Density
		{
			MagickGeometry^ get()
			{
				return gcnew MagickGeometry(Value->density());
			}
			void set(MagickGeometry^ value)
			{
				if (value == nullptr)
					return;

				Value->density(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Image depth (bits allocated to red/green/blue components).
		///</summary>
		//===========================================================================================
		property int Depth
		{
			int get()
			{
				return Value->depth();
			}
			void set(int value)
			{
				Value->depth(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Endianness (little like Intel or big like SPARC) for image formats which support
		/// endian-specific options.
		///</summary>
		//===========================================================================================
		property Endian Endian
		{
			ImageMagick::Endian get()
			{
				return (ImageMagick::Endian)Value->endian();
			}
			void set(ImageMagick::Endian value)
			{
				Value->endian((MagickCore::EndianType)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Exif profile (BLOB).
		///</summary>
		property MagickBlob^ ExifProfile
		{
			MagickBlob^ get()
			{
				Magick::Blob blob = Value->exifProfile();
				return gcnew MagickBlob(blob);
			}
			void set(MagickBlob^ value)
			{
				Value->exifProfile(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Image file size.
		///</summary>
		property long FileSize
		{
			long get()
			{
				return Value->fileSize();
			}
		}
		///==========================================================================================
		///<summary>
		/// Color to use when drawing inside an object.
		///</summary>
		property MagickColor^ FillColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->fillColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = value != nullptr ? value->CreateColor() : new Magick::Color();
				Value->fillColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Pattern to use while filling drawn objects.
		///</summary>
		property MagickImage^ FillPattern
		{
			MagickImage^ get()
			{
				Magick::Image* image = new Magick::Image(Value->fillPattern());
				return gcnew MagickImage(image);
			}
			void set(MagickImage^ value)
			{
				if (value == nullptr)
				{
					Magick::Image* image = new Magick::Image();
					Value->fillPattern(*image);
					delete image;
				}
				else
				{
					Value->fillPattern(*value->Value);
				}
			}
		}
		///==========================================================================================
		///<summary>
		/// Rule to use when filling drawn objects.
		///</summary>
		property FillRule FillRule
		{
			ImageMagick::FillRule get()
			{
				return (ImageMagick::FillRule)Value->fillRule();
			}
			void set(ImageMagick::FillRule value)
			{
				Value->fillRule((Magick::FillRule)value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Text rendering font.
		///</summary>
		property String^ Font
		{
			String^ get()
			{
				return Marshaller::Marshal(Value->font());
			}
			void set(String^ value)
			{
				std::string font;
				Value->font(Marshaller::Marshal(value, font));
			}
		}
		///==========================================================================================
		///<summary>
		/// Font point size.
		///</summary>
		property double FontPointsize
		{
			double get()
			{
				return Value->fontPointsize();
			}
			void set(double value)
			{
				Value->fontPointsize(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Height of the image.
		///</summary>
		property int Height
		{
			int get()
			{
				return Value->size().height();
			}
		}
		///==========================================================================================
		///<summary>
		/// The type of the image.
		///</summary>
		property ImageType ImageType
		{
			ImageMagick::ImageType get()
			{
				ImageMagick::ImageType result;

				if (!Enum::TryParse<ImageMagick::ImageType>(Marshaller::Marshal(Value->magick()), true, result))
					return ImageMagick::ImageType::Unknown;

				return result;
			}
			void set(ImageMagick::ImageType value)
			{
				if (value == ImageMagick::ImageType::Unknown)
					return;

				std::string name;

				Marshaller::Marshal(Enum::GetName(value.GetType(), value), name);
				Value->magick(name);
			}
		}
		///==========================================================================================
		///<summary>
		/// Returns the warning that occurred during the read operation.
		///</summary>
		property String^ ReadWarning
		{
			String^ get()
			{
				return _ReadWarning;
			}
		}
		///==========================================================================================
		///<summary>
		/// Color to use when drawing object outlines.
		///</summary>
		property MagickColor^ StrokeColor
		{
			MagickColor^ get()
			{
				return gcnew MagickColor(Value->strokeColor());
			}
			void set(MagickColor^ value)
			{
				Magick::Color* color = value != nullptr ? value->CreateColor() : new Magick::Color();
				Value->strokeColor(*color);
				delete color;
			}
		}
		///==========================================================================================
		///<summary>
		/// Stroke width for drawing lines, circles, ellipses, etc.
		///</summary>
		property double StrokeWidth
		{
			double get()
			{
				return Value->strokeWidth();
			}
			void set(double value)
			{
				Value->strokeWidth(value);
			}
		}
		///==========================================================================================
		///<summary>
		/// Width of the image.
		///</summary>
		property int Width
		{
			int get()
			{
				return Value->size().width();
			}
		}
		//===========================================================================================
		static bool operator == (MagickImage^ left, MagickImage^ right)
		{
			return Object::Equals(left, right);
		}
		//===========================================================================================
		static bool operator != (MagickImage^ left, MagickImage^ right)
		{
			return !Object::Equals(left, right);
		}
		//===========================================================================================
		static bool operator > (MagickImage^ left, MagickImage^ right)
		{
			return !(left < right) && (left != right);
		}
		//===========================================================================================
		static bool operator < (MagickImage^ left, MagickImage^ right)
		{
			Throw::IfNull("left", left);
			Throw::IfNull("right", right);

			return 
				(left->Value->rows() * left->Value->columns()) < 
				(right->Value->rows() * right->Value->columns());
		}
		//===========================================================================================
		static bool operator >= (MagickImage^ left, MagickImage^ right)
		{
			return (left > right) || (left == right);
		}
		//===========================================================================================
		static bool operator <= (MagickImage^ left, MagickImage^ right)
		{
			return (left < right) || (left == right);
		}
		///==========================================================================================
		///<summary>
		/// Adaptive-blur image with the default blur factor (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void AdaptiveBlur();
		///==========================================================================================
		///<summary>
		/// Adaptive-blur image with specified blur factor.
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void AdaptiveBlur(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Local adaptive threshold image.
		/// http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
		///</summary>
		///<param name="width">The width of the pixel neighborhood.</param>
		///<param name="height">The height of the pixel neighborhood.</param>
		///<exception cref="MagickException"/>
		void AdaptiveThreshold(int width, int height);
		///==========================================================================================
		///<summary>
		/// Local adaptive threshold image.
		/// http://www.dai.ed.ac.uk/HIPR2/adpthrsh.htm
		///</summary>
		///<param name="width">The width of the pixel neighborhood.</param>
		///<param name="height">The height of the pixel neighborhood.</param>
		///<param name="offset">Constant to subtract from pixel neighborhood mean.</param>
		///<exception cref="MagickException"/>
		void AdaptiveThreshold(int width, int height, long offset);
		///==========================================================================================
		///<summary>
		/// Add noise to image with the specified noise type.
		///</summary>
		///<param name="noiseType">The type of noise that should be added to the image.</param>
		///<exception cref="MagickException"/>
		void AddNoise(NoiseType noiseType);
		///==========================================================================================
		///<summary>
		/// Add noise to the specified channel of the image with the specified noise type.
		///</summary>
		///<param name="noiseType">The type of noise that should be added to the image.</param>
		///<param name="channel">The channel where the noise should be added.</param>
		///<exception cref="MagickException"/>
		void AddNoise(NoiseType noiseType, Channels channel);
		///==========================================================================================
		///<summary>
		/// Affine Transform image.
		///</summary>
		///<param name="affineMatrix">The affine matrix to use.</param>
		///<exception cref="MagickException"/>
		void AffineTransform(DrawableAffine^ affineMatrix);
		///==========================================================================================
		///<summary>
		/// Annotate using specified text, and bounding area.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="boundingArea">The bounding area.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, MagickGeometry^ boundingArea);
		///==========================================================================================
		///<summary>
		/// Annotate using specified text, bounding area, and placement gravity.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="boundingArea">The bounding area.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, MagickGeometry^ boundingArea, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Annotate using specified text, bounding area, and placement gravity.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="boundingArea">The bounding area.</param>
		///<param name="gravity">The placement gravity.</param>
		///<param name="degrees">The rotation.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, MagickGeometry^ boundingArea, Gravity gravity, double degrees);
		///==========================================================================================
		///<summary>
		/// Annotate with text (bounding area is entire image) and placement gravity.
		///</summary>
		///<param name="text">The text to use.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Annotate(String^ text, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Returns the value of a named image attribute.
		///</summary>
		///<param name="name">The name of the attribute.</param>
		String^ Attribute(String^ name);
		///==========================================================================================
		///<summary>
		/// Sets a named image attribute.
		///</summary>
		///<param name="name">The name of the attribute.</param>
		///<param name="value">The value of the attribute.</param>
		void Attribute(String^ name, String^ value);
		///==========================================================================================
		///<summary>
		/// Blur image with the default blur factor (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void Blur();
		///==========================================================================================
		///<summary>
		/// Blur image the specified channel of the image with the default blur factor (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void Blur(Channels channel);
		///==========================================================================================
		///<summary>
		/// Blur image with specified blur factor.
		///</summary>
		///<param name="radius">The radius of the Gaussian in pixels, not counting the center pixel.</param>
		///<param name="sigma">Tthe standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Blur(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Blur image with specified blur factor and channel.
		///</summary>
		///<param name="radius">The radius of the Gaussian in pixels, not counting the center pixel.</param>
		///<param name="sigma">Tthe standard deviation of the Laplacian, in pixels.</param>
		///<param name="channel">The channel that should be blurred.</param>
		///<exception cref="MagickException"/>
		void Blur(double radius, double sigma, Channels channel);
		///==========================================================================================
		///<summary>
		/// Border image (add border to image).
		///</summary>
		///<param name="color">The color of the border.</param>
		///<param name="width">The width of the border.</param>
		///<exception cref="MagickException"/>
		void Border(MagickColor^ color, int width);
		///==========================================================================================
		///<summary>
		/// Applies the color decision list from the specified ASC CDL file.
		///</summary>
		///<param name="fileName">The file to read the ASC CDL information from.</param>
		///<exception cref="MagickException"/>
		void CDL(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Returns the depth of the specified channel.
		///</summary>
		///<param name="channel">The channel to get the depth for.</param>
		///<exception cref="MagickException"/>
		int ChannelDepth(Channels channel);
		///==========================================================================================
		///<summary>
		/// Set the depth of the specified channel.
		///</summary>
		///<param name="channel">The channel to set the depth for.</param>
		///<param name="depth">The depth.</param>
		///<exception cref="MagickException"/>
		void ChannelDepth(Channels channel, int depth);
		///==========================================================================================
		///<summary>
		/// Charcoal effect image (looks like charcoal sketch).
		///</summary>
		///<exception cref="MagickException"/>
		void Charcoal();
		///==========================================================================================
		///<summary>
		/// Charcoal effect image (looks like charcoal sketch).
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Charcoal(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Chop image (remove vertical and horizontal subregion of image).
		///</summary>
		///<param name="xOffset">The X offset from origin.</param>
		///<param name="width">The width of the part to chop horizontally.</param>
		///<param name="yOffset">The Y offset from origin.</param>
		///<param name="height">The height of the part to chop vertically.</param>
		///<exception cref="MagickException"/>
		void Chop(int xOffset, int width, int yOffset, int height);
		///==========================================================================================
		///<summary>
		/// Chop image (remove vertical or horizontal subregion of image) using the specified geometry.
		///</summary>
		///<param name="geometry">The geometry to use.</param>
		///<exception cref="MagickException"/>
		void Chop(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Chop image (remove horizontal subregion of image).
		///</summary>
		///<param name="offset">The X offset from origin.</param>
		///<param name="width">The width of the part to chop horizontally.</param>
		///<exception cref="MagickException"/>
		void ChopHorizontal(int offset, int width);
		///==========================================================================================
		///<summary>
		/// Chop image (remove horizontal subregion of image).
		///</summary>
		///<param name="offset">The Y offset from origin.</param>
		///<param name="height">The height of the part to chop vertically.</param>
		///<exception cref="MagickException"/>
		void ChopVertical(int offset, int height);
		///==========================================================================================
		///<summary>
		/// Chromaticity blue primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaBluePrimary(double x, double y);
		///==========================================================================================
		///<summary>
		/// Chromaticity green primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaGreenPrimary(double x, double y);
		///==========================================================================================
		///<summary>
		/// Chromaticity red primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaRedPrimary(double x, double y);
		///==========================================================================================
		///<summary>
		/// Chromaticity red primary point.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		void ChromaWhitePoint(double x, double y);
		///==========================================================================================
		///<summary>
		/// Colorize image with the specified color, using specified percent opacity for red, green,
		/// and blue quantums
		///</summary>
		///<param name="opacityRedPercentage">The opacity percentage for red.</param>
		///<param name="opacityGreenPercentage">The opacity percentage for green.</param>
		///<param name="opacityBluePercentage">The opacity percentage for blue.</param>
		///<param name="color">The color to use.</param>
		///<exception cref="MagickException"/>
		void Colorize(int opacityRedPercentage, int opacityGreenPercentage, int opacityBluePercentage,
			MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Colorize image with the specified color, using specified percent opacity.
		///</summary>
		///<param name="opacityPercentage">The opacity percentage.</param>
		///<param name="color">The color to use.</param>
		///<exception cref="MagickException"/>
		void Colorize(int opacityPercentage, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Sets the alpha channel to the specified color.
		///</summary>
		///<param name="color">The color to use.</param>
		///<exception cref="MagickException"/>
		void ColorAlpha(MagickColor^ color);
		///==========================================================================================
		///<summary>
		// Get color at colormap position index.
		///</summary>
		///<param name="index">The position index.</param>
		///<exception cref="MagickException"/>
		MagickColor^ ColorMap(int index);
		///==========================================================================================
		///<summary>
		// Set color at colormap position index.
		///</summary>
		///<param name="index">The position index.</param>
		///<exception cref="MagickException"/>
		void ColorMap(int index, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Apply a color matrix to the image channels.
		///</summary>
		///<param name="matrixColor">The color matrix to use.</param>
		///<exception cref="MagickException"/>
		void ColorMatrix(MatrixColor^ matrixColor);
		///==========================================================================================
		///<summary>
		/// Compare current image with another image. Returns error information if the images are not
		/// identical.
		///</summary>
		///<param name="image">The other image to compare with this image.</param>
		///<exception cref="MagickException"/>
		CompareResult^ Compare(MagickImage^ image);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the 'In' operator.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="xOffset">The X offset from origin.</param>
		///<param name="yOffset">The Y offset from origin.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, long xOffset, long yOffset);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the specified algorithm.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="xOffset">The X offset from origin.</param>
		///<param name="yOffset">The Y offset from origin.</param>
		///<param name="compose">The algorithm to use.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, long xOffset, long yOffset, CompositeOperator compose);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the 'In' operator.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="offset">The offset from origin.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, MagickGeometry^ offset);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the specified algorithm.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="offset">The offset from origin.</param>
		///<param name="compose">The algorithm to use.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, MagickGeometry^ offset, CompositeOperator compose);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the 'In' operator.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, Gravity gravity);
		//==========================================================================================
		///<summary>
		/// Compose an image onto another at specified offset using the specified algorithm.
		///</summary>
		///<param name="image">The image to composite with this image.</param>
		///<param name="gravity">The placement gravity.</param>
		///<param name="compose">The algorithm to use.</param>
		///<exception cref="MagickException"/>
		void Composite(MagickImage^ image, Gravity gravity, CompositeOperator compose);
		//==========================================================================================
		///<summary>
		/// Contrast image (enhance intensity differences in image)
		///</summary>
		///<exception cref="MagickException"/>
		void Contrast();
		//==========================================================================================
		///<summary>
		/// Contrast image (enhance intensity differences in image)
		///</summary>
		///<param name="enhance">Use true to enhance the contrast and false to reduce the contrast.</param>
		///<exception cref="MagickException"/>
		void Contrast(bool enhance);
		//==========================================================================================
		///<summary>
		/// Convolve image. Applies a user-specified convolution to the image.
		///</summary>
		///<exception cref="MagickException"/>
		void Convolve(MatrixConvolve^ convolveMatrix);
		///==========================================================================================
		///<summary>
		/// Creates a copy of the current image.
		///</summary>
		MagickImage^ Copy();
		///==========================================================================================
		///<summary>
		/// Crop image (subregion of original image).
		///</summary>
		///<param name="geometry">The subregion to crop.</param>
		///<exception cref="MagickException"/>
		void Crop(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Crop image (subregion of original image) using CropPosition.Center.
		///</summary>
		///<param name="width">The width of the subregion.</param>
		///<param name="height">The height of the subregion.</param>
		///<exception cref="MagickException"/>
		void Crop(int width, int height);
		///==========================================================================================
		///<summary>
		/// Crop image (subregion of original image).
		///</summary>
		///<param name="width">The width of the subregion.</param>
		///<param name="height">The height of the subregion.</param>
		///<param name="gravity">The position where the cropping should start from.</param>
		///<exception cref="MagickException"/>
		void Crop(int width, int height,  Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Displaces an image's colormap by a given number of positions.
		///</summary>
		///<param name="amount">Displace the colormap this amount.</param>
		///<exception cref="MagickException"/>
		void CycleColormap(long amount);
		///==========================================================================================
		///<summary>
		/// Despeckle image (reduce speckle noise).
		///</summary>
		///<exception cref="MagickException"/>
		void Despeckle();
		///==========================================================================================
		///<summary>
		/// Distorts an image using various distortion methods, by mapping color lookups of the source
		/// image to a new destination image of the same size as the source image.
		///</summary>
		///<param name="method">The distortion method to use.</param>
		///<param name="arguments">An array containing the arguments for the distortion.</param>
		///<exception cref="MagickException"/>
		void Distort(DistortMethod method, array<double>^ arguments);
		///==========================================================================================
		///<summary>
		/// Distorts an image using various distortion methods, by mapping color lookups of the source
		/// image to a new destination image usually of the same size as the source image, unless
		/// 'bestfit' is set to true.
		///</summary>
		///<param name="method">The distortion method to use.</param>
		///<param name="arguments">An array containing the arguments for the distortion.</param>
		///<param name="bestfit">Attempt to 'bestfit' the size of the resulting image.</param>
		///<exception cref="MagickException"/>
		void Distort(DistortMethod method, array<double>^ arguments, bool bestfit);
		///==========================================================================================
		///<summary>
		/// Draw on image using a single drawable.
		///</summary>
		///<param name="drawable">The drawable to draw on the image.</param>
		///<exception cref="MagickException"/>
		void Draw(DrawableBase^ drawable);
		///==========================================================================================
		///<summary>
		/// Draw on image using a collection of drawables.
		///</summary>
		///<param name="drawables">The drawables to draw on the image.</param>
		///<exception cref="MagickException"/>
		void Draw(IEnumerable<DrawableBase^>^ drawables);
		///==========================================================================================
		///<summary>
		/// Determines whether the specified object is equal to the current image.
		///</summary>
		///<param name="obj">The object to compare this image with.</param>
		virtual bool Equals(Object^ obj) override;
		///==========================================================================================
		///<summary>
		/// Determines whether the specified image is equal to the current image.
		///</summary>
		///<param name="image">The image to compare this image with.</param>
		bool Equals(MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Edge image (hilight edges in image).
		///</summary>
		///<param name="radius">The radius of the pixel neighborhood.</param>
		///<exception cref="MagickException"/>
		void Edge(double radius);
		///==========================================================================================
		///<summary>
		/// Emboss image (hilight edges with 3D effect) with default value (0x1).
		///</summary>
		///<exception cref="MagickException"/>
		void Emboss();
		///==========================================================================================
		///<summary>
		/// Emboss image (hilight edges with 3D effect).
		///</summary>
		///<param name="radius">The radius of the Gaussian, in pixels, not counting the center pixel.</param>
		///<param name="sigma">The standard deviation of the Laplacian, in pixels.</param>
		///<exception cref="MagickException"/>
		void Emboss(double radius, double sigma);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<param name="backgroundColor">The background color to use.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry, MagickColor^ backgroundColor);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<param name="gravity">The placement gravity.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry, Gravity gravity);
		///==========================================================================================
		///<summary>
		/// Extend the image as defined by the geometry.
		///</summary>
		///<param name="geometry">The geometry to extend the image to.</param>
		///<param name="gravity">The placement gravity.</param>
		///<param name="backgroundColor">The background color to use.</param>
		///<exception cref="MagickException"/>
		void Extent(MagickGeometry^ geometry, Gravity gravity, MagickColor^ backgroundColor);
		///==========================================================================================
		///<summary>
		/// Flip image (reflect each scanline in the vertical direction).
		///</summary>
		///<exception cref="MagickException"/>
		void Flip();
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the  target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="color">The color to use.</param>
		///<exception cref="MagickException"/>
		void FloodFillColor(long x, long y, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the  target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="geometry">The position of the pixel.</param>
		///<param name="color">The color to use.</param>
		///<exception cref="MagickException"/>
		void FloodFillColor(MagickGeometry^ geometry, MagickColor^ color);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the  target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="color">The color to use.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFillColor(long x, long y, MagickColor^ color, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flood-fill color across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="geometry">The position of the pixel.</param>
		///<param name="color">The color to use.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFillColor(MagickGeometry^ geometry, MagickColor^ color, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Floodfill pixels matching color (within fuzz factor) of target pixel(x,y) with replacement
		/// opacity value using method.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="opacity">The opacity to use.</param>
		///<param name="paintMethod">The paint method to use.</param>
		///<exception cref="MagickException"/>
		void FloodFillOpacity(long x, long y, int opacity, PaintMethod paintMethod);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="image">The image to use.</param>
		///<exception cref="MagickException"/>
		void FloodFillTexture(long x, long y, MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="geometry">The position of the pixel.</param>
		///<param name="image">The image to use.</param>
		///<exception cref="MagickException"/>
		void FloodFillTexture(MagickGeometry^ geometry, MagickImage^ image);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="x">The X coordinate.</param>
		///<param name="y">The Y coordinate.</param>
		///<param name="image">The image to use.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFillTexture(long x, long y, MagickImage^ image, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flood-fill texture across pixels that match the color of the target pixel and are neighbors
		/// of the target pixel. Uses current fuzz setting when determining color match.
		///</summary>
		///<param name="geometry">The position of the pixel.</param>
		///<param name="image">The image to use.</param>
		///<param name="borderColor">The color of the border.</param>
		///<exception cref="MagickException"/>
		void FloodFillTexture(MagickGeometry^ geometry, MagickImage^ image, MagickColor^ borderColor);
		///==========================================================================================
		///<summary>
		/// Flop image (reflect each scanline in the horizontal direction).
		///</summary>
		///<exception cref="MagickException"/>
		void Flop();
		///==========================================================================================
		///<summary>
		/// Obtain font metrics for text string given current font, pointsize, and density settings.
		///</summary>
		///<exception cref="MagickException"/>
		TypeMetric^ FontTypeMetrics(String^ text);
		///==========================================================================================
		///<summary>
		/// Long image format description
		///</summary>
		///<exception cref="MagickException"/>
		String^ Format();
		///==========================================================================================
		///<summary>
		/// Frame image with the default geometry (25x25+6+6).
		///</summary>
		///<exception cref="MagickException"/>
		void Frame();
		///==========================================================================================
		///<summary>
		/// Frame image with the specified geometry.
		///</summary>
		///<param name="geometry">The geometry of the frame.</param>
		///<exception cref="MagickException"/>
		void Frame(MagickGeometry^ geometry);
		///==========================================================================================
		///<summary>
		/// Frame image with the specified with and height.
		///</summary>
		///<param name="width">The width of the frame.</param>
		///<param name="height">The height of the frame.</param>
		///<exception cref="MagickException"/>
		void Frame(int width, int height);
		///==========================================================================================
		///<summary>
		/// Frame image with the specified with, height, innerBevel and outerBevel.
		///</summary>
		///<param name="width">The width of the frame.</param>
		///<param name="height">The height of the frame.</param>
		///<param name="innerBevel">The inner bevel of the frame.</param>
		///<param name="outerBevel">The outer bevel of the frame.</param>
		///<exception cref="MagickException"/>
		void Frame(int width, int height, long innerBevel, long outerBevel);
		///==========================================================================================
		///<summary>
		/// Applies a mathematical expression to the image.
		///</summary>
		///<param name="expression">The expression to apply.</param>
		///<exception cref="MagickException"/>
		void Fx(String^ expression);
		///==========================================================================================
		///<summary>
		/// Applies a mathematical expression to the image.
		///</summary>
		///<param name="expression">The expression to apply.</param>
		///<param name="channel">The channel(s) to apply the expression to.</param>
		///<exception cref="MagickException"/>
		void Fx(String^ expression, Channels channel);
		///==========================================================================================
		///<summary>
		/// Gamma level of the image.
		///</summary>
		///<exception cref="MagickException"/>
		double Gamma();
		///==========================================================================================
		///<summary>
		/// Gamma correct image.
		///</summary>
		///<param name="value">The image gamma.</param>
		///<exception cref="MagickException"/>
		void Gamma(double value);
		///==========================================================================================
		///<summary>
		/// Gamma correct image.
		///</summary>
		///<param name="gammeRed">The image gamma for the red channel.</param>
		///<param name="gammeGreen">The image gamma for the green channel.</param>
		///<param name="gammeBlue">The image gamma for the blue channel.</param>
		///<exception cref="MagickException"/>
		void Gamma(double gammeRed, double gammeGreen, double gammeBlue);
		///==========================================================================================
		///<summary>
		/// Gaussian blur image.
		///</summary>
		///<param name="width">The number of neighbor pixels to be included in the convolution.</param>
		///<param name="sigma">The standard deviation of the gaussian bell curve.</param>
		///<exception cref="MagickException"/>
		void GaussianBlur(double width, double sigma);
		///==========================================================================================
		///<summary>
		/// Gaussian blur image.
		///</summary>
		///<param name="width">The number of neighbor pixels to be included in the convolution.</param>
		///<param name="sigma">The standard deviation of the gaussian bell curve.</param>
		///<param name="channel">The channel(s) to blur.</param>
		///<exception cref="MagickException"/>
		void GaussianBlur(double width, double sigma, Channels channel);
		///==========================================================================================
		///<summary>
		/// Preferred size of the image when encoding.
		///</summary>
		///<exception cref="MagickException"/>
		MagickGeometry^ Geometry();
		///==========================================================================================
		///<summary>
		/// Servers as a hash of this type.
		///</summary>
		virtual int GetHashCode() override;
		///==========================================================================================
		///<summary>
		/// Retrieve a named profile from the image.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<exception cref="MagickException"/>
		MagickBlob^ Profile(String^ name);
		///==========================================================================================
		///<summary>
		/// Add a named profile to an image or remove a named profile by passing null.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<param name="blob">A blob containing the profile.</param>
		///<exception cref="MagickException"/>
		void Profile(String^ name, MagickBlob^ blob);
		///==========================================================================================
		///<summary>
		/// Add a named profile to an image or remove a named profile by passing null.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<param name="stream">A stream containing the profile.</param>
		///<exception cref="MagickException"/>
		void Profile(String^ name, Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Add a named profile to an image or remove a named profile by passing null.
		///</summary>
		///<param name="name">The name of the profile (e.g. "ICM", "IPTC", or a generic profile name).</param>
		///<param name="fileName">The file to read the profile from.</param>
		///<exception cref="MagickException"/>
		void Profile(String^ name, String^ fileName);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="blob">The blob to read the image data from.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(MagickBlob^ blob);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="blob">The blob to read the image data from.</param>
		///<param name="colorSpace">The colorspace to convert the image to.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(MagickBlob^ blob, ImageMagick::ColorSpace colorSpace);
		///==========================================================================================
		///<summary>
		/// Read single vector image frame.
		///</summary>
		///<param name="blob">The blob to read the image data from.</param>
		///<param name="width">The width of the image.</param>
		///<param name="height">The height of the image.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(MagickBlob^ blob, int width, int height);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<param name="colorSpace">The colorspace to convert the image to.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(String^ fileName, ImageMagick::ColorSpace colorSpace);
		///==========================================================================================
		///<summary>
		/// Read single vector image frame.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<param name="width">The width of the image.</param>
		///<param name="height">The height of the image.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(String^ fileName, int width, int height);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(Stream^ stream);
		///==========================================================================================
		///<summary>
		/// Read single image frame.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<param name="colorSpace">The colorspace to convert the image to.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(Stream^ stream, ImageMagick::ColorSpace colorSpace);
		///==========================================================================================
		///<summary>
		/// Read single vector image frame.
		///</summary>
		///<param name="stream">The stream to read the image data from.</param>
		///<param name="width">The width of the image.</param>
		///<param name="height">The height of the image.</param>
		///<exception cref="MagickException"/>
		static MagickImage^ Read(Stream^ stream, int width, int height);
		///==========================================================================================
		///<summary>
		/// Separates a channel from the image and makes it a grayscale image.
		///</summary>
		///<param name="channel">The channel to separates.</param>
		void Separate(Channels channel);
		///==========================================================================================
		///<summary>
		/// Converts this instance to a MagickBlob.
		///</summary>
		MagickBlob^ ToBlob();
		///==========================================================================================
		///<summary>
		/// Returns a string that represents the current image.
		///</summary>
		virtual String^ ToString() override;
		///==========================================================================================
		///<summary>
		/// Writes the image to the specified file name.
		///</summary>
		///<param name="fileName">The fully qualified name of the image file, or the relative image file name.</param>
		///<exception cref="MagickException"/>
		void Write(String^ fileName);
		///==========================================================================================
		///<summary>
		/// Writes the image to the specified stream.
		///</summary>
		///<param name="stream">The stream to write the image data to.</param>
		///<exception cref="MagickException"/>
		void Write(Stream^ stream);
		//===========================================================================================
	};
	//==============================================================================================
}