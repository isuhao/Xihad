#pragma once
#include <Engine/position2d.h>
#include <Engine/dimension2d.h>
#include <irrlicht/IReferenceCounted.h>
#include <algorithm>

namespace xihad { namespace dialogue 
{
	class CTextSection;
	class CAlignedTextSection;
	class ITextSectionSplitter;
	class CDialogueAlignmenter : public virtual irr::IReferenceCounted
	{
	public:
		explicit CDialogueAlignmenter(unsigned widthLimit, 
			ngn::dimension2di kerningNewLine = ngn::dimension2di());
		
		virtual ~CDialogueAlignmenter() {}

		virtual void newLine();

		virtual int insert(CTextSection& section);

		virtual void reset();

		unsigned getTotalHeight() const;

		CAlignedTextSection* getDialogueHead() const
		{
			return mDialogueHead;
		}

////////////////////////////////////////////////////
/// CONFIG OPTIONS
///////////////////////////////////////////////////
		unsigned getWidthLimit() const
		{
			return mWidthLimit;
		}

		void setWidthLimit(unsigned w);

		int getCurrentLineHeight() const
		{
			return mCurrentLineHeight;
		}

		void setKerningHeight(int height)
		{
			mKerningHeight = height;
		}

		int getKerningHeight() const 
		{
			return mKerningHeight;
		}
		
		void setKerningNewLine(ngn::dimension2di knl)
		{
			mKerningNewLine = knl;
			checkKNL();
		}

		ngn::dimension2di getKerningNewLine() const 
		{
			return mKerningNewLine;
		}

	protected:
		CAlignedTextSection* getLineHead()
		{
			return mCurrentLineHead;
		}

		virtual void onLineFilled();

	private:
		void checkKNL()
		{
			if (mKerningNewLine.Width > 0)
				mKerningNewLine.Width = std::min((unsigned) mKerningNewLine.Width, mWidthLimit);
		}

		void wrapLine()
		{
			mRelativeOffsetToPrev = ngn::position2di(-mOffset.X, mCurrentLineHeight);
			mOffset.X = 0;
			mOffset.Y += mCurrentLineHeight;
			mCurrentLineHeight = 0;
			mCurrentLineHead = nullptr;
		}

		void advanceLine(unsigned horizontalDistance, int height)
		{
			mCurrentLineHeight = std::max(mCurrentLineHeight, height);
			mOffset.X += horizontalDistance;
			mRelativeOffsetToPrev.X = horizontalDistance;
			mRelativeOffsetToPrev.Y = 0;
		}

		int insertNonEmptySection(CAlignedTextSection* section);

		void linkNewSection(CAlignedTextSection* newSection);

	private:
		unsigned mWidthLimit;
		int mKerningHeight;
		ngn::dimension2di mKerningNewLine;

		int mCurrentLineHeight;
		ngn::position2di mRelativeOffsetToPrev;
		ngn::position2di mOffset;
		CAlignedTextSection* mDialogueHead;
		CAlignedTextSection* mCurrentLineHead;
		CAlignedTextSection* mLastInserted;
	};
}}
