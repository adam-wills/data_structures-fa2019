/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     std::map<Point<3>,TileImage*> pointToTile;
     vector<Point<3>> points(0);
     for (TileImage& tile : theTiles) {
       Point<3> point = convertToXYZ(tile.getAverageColor());
       if (pointToTile.find(point) == pointToTile.end()) {
         points.push_back(point);
         pointToTile[point] = &tile;
       }
     }
     KDTree<3>* tileTree = new KDTree<3>(points);

     int numRows = theSource.getRows();
     int numCols = theSource.getColumns();
     MosaicCanvas* newCanvas = new MosaicCanvas(numRows,numCols);
     for (int i = 0; i < numRows; ++i) {
       for (int j = 0; j < numCols; ++j) {
         Point<3> regionColor = convertToXYZ(theSource.getRegionColor(i,j));
         Point<3> nearestPoint = tileTree->findNearestNeighbor(regionColor);
         newCanvas->setTile(i,j,pointToTile[nearestPoint]);
       }
     }
     delete tileTree;
     return newCanvas;

}
