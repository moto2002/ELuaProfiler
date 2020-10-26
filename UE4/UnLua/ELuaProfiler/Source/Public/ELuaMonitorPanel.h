// The MIT License (MIT)

// Copyright 2020 HankShu inkiu0@gmail.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include "CoreMinimal.h"
#include "ELuaTraceInfoNode.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Views/STreeView.h"
#include "Widgets/Docking/SDockTab.h"

enum ELuaMonitorMode : uint8
{
	PerFrame,		// Deep Copy TraceInfoTree PerFrame
	Total,			// Only one TraceInfoTree
	Statistics,		// Unfold TraceInfoTree
	MAX
};

class SELuaMonitorPanel
{
public:
	SELuaMonitorPanel();
	~SELuaMonitorPanel();

    TSharedRef<class SDockTab> GetSDockTab();

	TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FELuaTraceInfoNode> TINode, const TSharedRef<STableViewBase>& OwnerTable);

	void OnGetChildrenRaw(TSharedPtr<FELuaTraceInfoNode> Parent, TArray<TSharedPtr<FELuaTraceInfoNode>>& OutChildren);

	void Tick(float DeltaTime);

	void OnDestroy();

private:
	FReply OnForwardBtnClicked();

	FReply OnClearBtnClicked();

	const FSlateBrush* GetPrevFrameIcon() const;

	const FSlateBrush* GetForwardIcon() const;

	const FSlateBrush* GetNextFrameIcon() const;

	void UpdateRoot();

	void OnModeChanged(float InMode);

private:
	TSharedPtr<STreeView<TSharedPtr<FELuaTraceInfoNode>>> TreeViewWidget;

	TSharedPtr<FELuaTraceInfoNode> CurRootTINode;

	TArray<TSharedPtr<FELuaTraceInfoNode>> ShowRootList;

	TSharedPtr<SButton> PrevFrameBtn;

	TSharedPtr<SButton> ForwardBtn;

	TSharedPtr<SButton> NextFrameBtn;

	TSharedPtr<SButton> ClearBtn;

	ELuaMonitorMode MonitorMode = Total;

	float ElapsedTime = 0.f;

	const static int32 COL_WIDTH = 80;

	const static int32 UPDATE_INTERVAL = 0.5;
};
