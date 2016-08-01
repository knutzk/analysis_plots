// -*- mode: c++; -*-
#ifndef PLOTTING_HISTPLOTTER_H_
#define PLOTTING_HISTPLOTTER_H_

#include "Plotting/AtlasLabel.h"
#include "Plotting/AtlasStyle.h"
#include <TCanvas.h>
#include <TError.h>
#include <TLegend.h>
#include <memory>

class string;
namespace plotting {
class HistHolder;
class HistHolderContainer;
}

/*
 * Class to plot histograms.
 */
namespace plotting {
class HistPlotter {
 public:
  /*
   * Default constructor
   */
  HistPlotter() {
    SetAtlasStyle();
    gErrorIgnoreLevel = 2000;
    initCanvas();
    initLegend();
  }

  /*
   * Destructor
   */
  virtual ~HistPlotter() {}

  /*
   * Add a histogram to the legend.
   * @param The HistHolder object of the histogram.
   */
  virtual void addToLegend(const HistHolder& hist);

  /*
   * Add a set of histograms to the legend.
   * @param The HistHolderContainer object of the histograms.
   */
  virtual void addToLegend(const HistHolderContainer& hist_container);

  /*
   * Create a new instance of a TCanvas object.
   * @param Desired width of the canvas.
   * @param Desired height of the canvas.
   */
  virtual void initCanvas(unsigned const int& width = 600,
                          unsigned const int& height = 600);

  /*
   * Create a new instance of a TLegend object.
   * @param Lower x boundary of the legend.
   * @param Lower y boundary of the legend.
   * @param Upper x boundary of the legend.
   * @param Upper y boundary of the legend.
   */
  virtual void initLegend(const double& x1 = 0.57, const double& y1 = 0.78,
                          const double& x2 = 0.91, const double& y2 = 0.92);

  /*
   * Plot the ATLAS label.
   */
  inline void plotAtlasLabel() { atlas_label_.plot(); }

  /*
   * Plot the legend.
   */
  inline void plotLegend() { legend_->Draw("SAME"); }

  /*
   * Reset the canvas and the legend.
   * 
   * REMARK: We need these reset functions to make sure that ROOT does
   * not conflict with the object ownership of the unique pointers
   * (these functions release the allocated memory, then let ROOT take
   * care of it).
   */
  virtual void resetCanvas();
  virtual void resetLegend();

  /*
   * Save the current drawings on mCanvas to a file.
   * @param Title of the file.
   */
  virtual void saveToFile(const std::string& title);

  /*
   * Get a pointer to the AtlasLabel object.
   * @return Pointer to the AtlasLabel.
   */
  inline AtlasLabel* getAtlasLabel() { return &atlas_label_; }

  /*
   * Get a pointer to the TLegend object.
   * @return Pointer to the TLegened.
   */
  inline TLegend* getLegend() { return legend_.get(); }

  /*
   * Get a pointer to the TCanvas object.
   * @return Pointer to the TCanvas.
   */
  inline TCanvas* getCanvas() { return canvas_.get(); }


  void setDoVerbose(const bool& b = true) { do_verbose_ = b; }
  inline bool getDoVerbose() const { return do_verbose_; }

  void setExportToEPS(const bool& b = true) { export_to_eps_ = b; }
  inline bool getExportToEPS() const { return export_to_eps_; }

  void setExportToPDF(const bool& b = true) { export_to_pdf_ = b; }
  inline bool getExportToPDF() const { return export_to_pdf_; }

  void setExportToPNG(const bool& b = true) { export_to_png_ = b; }
  inline bool getExportToPNG() const { return export_to_png_; }

  void setFileDir(const std::string& dir) { file_dir_ = dir; }
  inline std::string getFileDir() const { return file_dir_; }

  void setOutputDir(const std::string& dir) { output_dir_ = dir; }
  inline std::string getOutputDir() const { return output_dir_; }

 protected:
  AtlasLabel atlas_label_{};
  Double_t legend_x1_{0};
  Double_t legend_x2_{0};
  Double_t legend_y1_{0};
  Double_t legend_y2_{0};
  bool do_verbose_{false};
  bool export_to_eps_{false};
  bool export_to_pdf_{true};
  bool export_to_png_{false};
  std::string file_dir_{"./"};
  std::string output_dir_{"./"};
  std::unique_ptr<TCanvas> canvas_{nullptr};
  std::unique_ptr<TLegend> legend_{nullptr};
  unsigned int canvas_height_{0};
  unsigned int canvas_width_{0};
};
}  // namespace plotting

#endif  // PLOTTING_HISTPLOTTER_H_
