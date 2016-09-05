// -*- mode: c++; -*-
// Copyright 2016 <Knut Zoch> <kzoch@cern.ch>
#ifndef HISTPLOTTER_H_
#define HISTPLOTTER_H_

#include <memory>
#include <string>
#include <TCanvas.h>
#include <TLegend.h>
#include "core/plotters/atlas_label.h"

namespace plotting {
class HistHolder;
class HistHolderContainer;
}

namespace plotting {
/**
 * Manage canvas, legend etc. to plot histograms. This takes care of
 * all the legend settings, canvas size and saving the output to
 * different file formats.
 */
class HistPlotter {
 public:
  //! The default constructor
  HistPlotter();

  //! The destructor
  virtual ~HistPlotter();

  /**
   * Add a HistHolder objects to the legend. This will take into
   * account the legend options that are set within the HistHolder
   * object.
   *
   * @param hist The HistHolder object managing the histogram
   */
  virtual void addToLegend(const HistHolder& hist);

  /**
   * Add a whole container of histograms to the legend. This will take
   * the individual legend options into account that are set for the
   * HistHolder objects within the container.
   *
   * @param hist_container The HistHolderContainer object of the histograms
   */
  virtual void addToLegend(const HistHolderContainer& hist_container);

  /**
   * Create a new instance of a TCanvas object. This will safely check
   * whether a canvas had been initialised before and free the
   * corresponding memory, if necessary. It also avoids the warning
   * 'replacing canvas with same name' by letting ROOT remove the
   * canvas from the internal list.
   *
   * @param width Desired width of the canvas.
   * @param height Desired height of the canvas.
   */
  virtual void initCanvas(const int& width = 600, const int& height = 600);

  /**
   * Create a new instance of a TLegend object. This will safely check
   * whether a legend had been initialised before and free the
   * corresponding memory, if necessary.
   *
   * @param x1 Lower x boundary of the legend.
   * @param y1 Lower y boundary of the legend.
   * @param x2 Upper x boundary of the legend.
   * @param y2 Upper y boundary of the legend.
   */
  virtual void initLegend(const double& x1 = 0.57, const double& y1 = 0.78,
                          const double& x2 = 0.91, const double& y2 = 0.92);

  //! Plot the ATLAS label associated with this class.
  inline void plotAtlasLabel() { atlas_label_->plot(); }

  //! Plot the legend associated with this class.
  inline void plotLegend() { legend_->Draw("SAME"); }

  /**
   * Reset the canvas, i.e. free the allocated memory and reset the
   * unique pointer. Remark: We need these reset functions to make
   * sure that ROOT does not conflict with the object ownership of the
   * unique pointers (these functions release the allocated memory,
   * then let ROOT take care of the deletion).
   */
  virtual void resetCanvas();

  /**
   * Reset the legend, i.e. free the allocated memory and reset the
   * unique pointer. Remark: We need these reset functions to make
   * sure that ROOT does not conflict with the object ownership of the
   * unique pointers (these functions release the allocated memory,
   * then let ROOT take care of the deletion).
   */
  virtual void resetLegend();

  /**
   * Save the currently drawn objects to a file. According to the set
   * booleans, this will save to the following possible output
   * formats: PDF, PNG, EPS.
   *
   * @param title The desired name of the file (w/o extension)
   */
  virtual void saveToFile(const std::string& title);

  //! Get a pointer to the AtlasLabel object associated with this
  //! class. Internally the ATLAS label is managed with a unique
  //! pointer to safely take care of the allocated memory.
  inline AtlasLabel* getAtlasLabel() { return atlas_label_.get(); }

  //! Get a pointer to the TLegend object associated with this
  //! class. Internally the legend is managed with a unique pointer to
  //! safely take care of the allocated memory.
  inline TLegend* getLegend() { return legend_.get(); }

  //! Get a pointer to the TCanvas object associated with this
  //! class. Internally the canvas is managed with a unique pointer to
  //! safely take care of the allocated memory.
  inline TCanvas* getCanvas() { return canvas_.get(); }

  //! Get whether the class is set to be verbosive.
  inline bool getDoVerbose() const { return do_verbose_; }
  //! Get whether to export to EPS files when saving.
  inline bool getExportToEPS() const { return export_to_eps_; }
  //! Get whether to export to PDF files when saving.
  inline bool getExportToPDF() const { return export_to_pdf_; }
  //! Get whether to export to PNG files when saving.
  inline bool getExportToPNG() const { return export_to_png_; }
  //! Get the output directory set within this class.
  inline std::string getOutputDir() const { return output_dir_; }

  //! Set whether this class should be verbosive.
  inline void setDoVerbose(const bool& b = true) { do_verbose_ = b; }
  //! Set whether to export to EPS file when saving.
  inline void setExportToEPS(const bool& b = true) { export_to_eps_ = b; }
  //! Set whether to export to PDF file when saving.
  inline void setExportToPDF(const bool& b = true) { export_to_pdf_ = b; }
  //! Set whether to export to PnG file when saving.
  inline void setExportToPNG(const bool& b = true) { export_to_png_ = b; }
  //! Set the output directory for saving.
  inline void setOutputDir(const std::string& dir) { output_dir_ = dir; }

 protected:
  //! The unique pointer managing the ATLAS label.
  std::unique_ptr<AtlasLabel> atlas_label_{new AtlasLabel{}};
  //! The unique pointer managing the TCanvas object.
  std::unique_ptr<TCanvas> canvas_{nullptr};
  //! The unique pointer managing the TLegend object.
  std::unique_ptr<TLegend> legend_{nullptr};
  //! Boolean to decide whether the class is verbosive.
  bool do_verbose_{false};

 private:
  bool export_to_eps_{false};
  bool export_to_pdf_{true};
  bool export_to_png_{false};
  double legend_x1_{0};
  double legend_x2_{0};
  double legend_y1_{0};
  double legend_y2_{0};
  int canvas_height_{0};
  int canvas_width_{0};
  std::string file_dir_{"./"};
  std::string output_dir_{"./"};
};
}  // namespace plotting

#endif  // HISTPLOTTER_H_
