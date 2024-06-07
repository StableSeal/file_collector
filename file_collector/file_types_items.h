#pragma once
#include <string>
#include <vector>
#include <objidl.h>
#include <gdiplus.h>
#include <Windows.h>
#pragma comment(lib, "gdiplus.lib")

namespace file_collector 
{

  struct item
  {
    std::wstring file_path;
    float x = 0.0f;
    float y = 0.0f;
  };
  struct item_list 
  {
    bool pending_change = true;
    std::vector<::file_collector::item> item_vector;
  };

  struct click_range
  {
    float x = .2f;
    float y = .2f;
  };

  void add_item(item_list &Item_list, item Item);
  void delete_item(item_list &Item_list, int index);
  int find_item_by_position(item_list &Item_list, click_range &Click_range, float x, float y);
  
  void start();
  void redraw();
  void stop();

  void draw_button(int window_size_x, int window_size_y, HDC hdc, item_list& list);
}

extern int item_search(file_collector::item_list& Item_list, file_collector::click_range& Click_Range, float x, float y, int i);
extern bool click_in_bounds(float x, float y, float click_x, float click_y, file_collector::click_range Click_range);




