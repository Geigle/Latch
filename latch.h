/*!
 * 	\file		latch.h
 * 	\class		Latch
 * 	\author		Gage Geigle	<mailto:gage@gagegeigle.com>
 * 	\copyright	2018 Gage Geigle
 * 	\note		Freely distributed under MIT license.
 */

/* Std Includes */
#include <functional>


/*!
 *	\class	Latch
 * 	\brief	This class simulates a physical latch, allowing an action to occur
 * only once, until it is unset, optionally performing a different action.
 * 	\tparam	retT	-	This specifies the return type that this latch will use.
 * 	\tparam	argT	-	This specifies the argument type that this latch will
 * use.
 */
template<typename retT, typename argT>
class Latch
{
public:
    Latch(std::function<retT(argT)> f_set = nullptr,
          std::function<retT(argT)> f_unset = nullptr):
        fSet{f_set},
        fUnset{f_unset}
    {
        isSet = false;
        didFlip = false;
        fReturn = nullptr;
    }

    ~Latch()
    {
        if(fReturn != nullptr)
        {
            delete fReturn;
        }
    }


    /*!
     * \brief init() is used to set the function(s) that the latch will use.
     * \param f_set	-	The function that set() will use.
     * \param f_unset	-	The function that unset() will use.
     */
    void init(std::function<retT(argT)> f_set = nullptr,
              std::function<retT(argT)> f_unset = nullptr)
    {
        fSet = f_set;
        fUnset = f_unset;
    }

    /*!
     * \brief 	set() will call the function assigned in constructor or init()
     * if the latch is not already set.
     * \param 	arg	-	The argument that the assigned function requires.
     */
    void set(argT arg)
    {
        if(fReturn != nullptr)
        {
            delete fReturn;
        }

        fReturn = new retT;
        didFlip = false;

        if(!isSet)
        {
            isSet = true;
            didFlip = true;
            if(fSet != nullptr)
            {
                *fReturn = fSet(arg);
            }
        }
    }

    /*!
     * \brief 	unset() will call the function assigned in constructor or init()
     * if the latch is not already unset.
     * \param 	arg	-	The argument that the assigned function requires.
     */
    void unset(argT arg)
    {
        if(fReturn != nullptr)
        {
            delete fReturn;
        }

        fReturn = new retT;
        didFlip = false;

        if(isSet)
        {
            isSet = false;
            didFlip = true;
            if(fUnset != nullptr)
            {
                *fReturn = fUnset(arg);
            }
        }
    }

    /*!
     * \brief	flipped() tells if the last set() or unset() call flipped the
     * latch.
     * \return	true	-	The latch flipped.
     * \return	false	-	The latch did not flip.
     */
    bool flipped()
    {
        return didFlip;
    }

    /*!
     * \brief result() returns the captured output of the function assigned in
     * constructor or init().
     * \return	retT	-	The return type specified at construction.
     */
    retT result()
    {
        return *fReturn;
    }

private:
    std::function<retT(argT)> fSet;		/*!< Function to call when setting the
                                          latch. */
    std::function<retT(argT)> fUnset;	/*!< Function to call when unsetting
                                          the latch. */
    retT* fReturn;	/*!< Stores the last output of fSet of fUnset. */
    bool isSet;		/*!< Stores the set/unset status of the latch. */
    bool didFlip;	/*!< Stores whether the last call to set() or unset()
                      resulted in a transition. */
};
