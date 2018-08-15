/**
 * @file sourceimage.h
 *
 * Definition of the SourceImage class.
 *
 * @author Matt Sachtler
 * @author Scott Wegner
 * @date Fall 2008
 *
 * @author Aria Buckles
 * @date Fall 2011
 */
#ifndef _SOURCEIMAGE_H
#define _SOURCEIMAGE_H

#include <stdint.h>

#include "easypng.h"

using namespace std;

/**
 * SourceImage provides some additional data and functions suitable for the
 * source image for the photomosaic. The default constructor will take a
 * number of rows and columns to divide the image into.  The image will
 * then be processes to find the average color of each
 * region.
 */
class SourceImage
{
	public:
		SourceImage(const PNG & image, int resolution);

		/**
		 * Get the average color of a particular region.  Note, the
		 * row and column should be specified with a 0-based index.
		 * i.e., The top-left corner is (row, column) (0,0).
		 *
		 * @param row The row of the particular region in the image
		 * @param col The column of the particular region in the image
		 *
		 * @return The average color of the image
		 */
		RGBAPixel getRegionColor(int row, int col) const;

		/**
		 * Retreive the number of row sub-regions the source image
		 * is broken into.
		 *
		 * @return The number of rows, or -1 if in an invalid state
		 */
		int getRows() const;

		/**
		 * Retreive the number of column sub-regions the source
		 * image is broken into.
		 *
		 * @return The number of columns, or -1 if in an invalid state
		 */
		int getColumns() const;

	private:
		PNG backingImage;
		int resolution;

		static uint64_t divide(uint64_t a, uint64_t b);
};

#endif /* _SOURCEIMAGE_H */
