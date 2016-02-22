/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2015 Christian Kreuzberger and Daniel Posch, Alpen-Adria-University
 * Klagenfurt
 *
 * This file is part of amus-ndnSIM, based on ndnSIM. See AUTHORS for complete list of
 * authors and contributors.
 *
 * amus-ndnSIM and ndnSIM are free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * amus-ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * amus-ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include "adaptation-logic-buffer-based.h"
#include "multimedia-player.h"


namespace dash
{
namespace player
{

ENSURE_ADAPTATION_LOGIC_INITIALIZED(BufferBasedAdaptationLogic)

ISegmentURL*
BufferBasedAdaptationLogic::GetNextSegment(unsigned int *requested_segment_number,
                                                  const dash::mpd::IRepresentation **usedRepresentation, bool *hasDownloadedAllSegments)
{
  if(currentSegmentNumber < getTotalSegments ())
    *hasDownloadedAllSegments = false;
  else
  {
    *hasDownloadedAllSegments = true;
    return NULL; // everything downloaded
  }

  const IRepresentation* useRep = NULL;;

  double speed_of_last_rep = 0.0;

  double cur_download_speed = this->m_multimediaPlayer->GetLastDownloadBitRate();


  if (lastUsedRep != NULL)
  {
    speed_of_last_rep = lastUsedRep->GetBandwidth();
    useRep = lastUsedRep;


    if (this->m_multimediaPlayer->GetBufferLevel() < 8) {
      // whatever representation it is, decrease it
      double highest_bitrate = 0.0;

      RepresentationsMap::iterator it;

      // for (auto& keyValue : *(this->m_availableRepresentations))
      for ( it = m_availableRepresentations->begin(); it != m_availableRepresentations->end(); it++)
      {
        const IRepresentation* rep = it->second;
        // std::cerr << "Rep=" << keyValue.first << " has bitrate " << rep->GetBandwidth() << std::endl;
        if (rep->GetBandwidth() < speed_of_last_rep && rep->GetBandwidth() < cur_download_speed)
        {
          if (rep->GetBandwidth() > highest_bitrate)
          {
            useRep = rep;
            highest_bitrate = rep->GetBandwidth();
          }
        }
      }

    } else if (this->m_multimediaPlayer->GetBufferLevel() < 14) {
      // stay at this representation, do not modify userep
    } else { // >= 16
      // time to increase to the next best representation
      fprintf(stderr, "trying to increase from %f\n", speed_of_last_rep);
      double highest_bitrate = 999999999.99;

      RepresentationsMap::iterator it;

      // for (auto& keyValue : *(this->m_availableRepresentations))
      for ( it = m_availableRepresentations->begin(); it != m_availableRepresentations->end(); it++)
      {
        const IRepresentation* rep = it->second;
        // std::cerr << "Rep=" << keyValue.first << " has bitrate " << rep->GetBandwidth() << std::endl;
        if (rep->GetBandwidth() > speed_of_last_rep && rep->GetBandwidth() < cur_download_speed)
        {
          if (rep->GetBandwidth() < highest_bitrate)
          {
            useRep = rep;
            highest_bitrate = rep->GetBandwidth();
          }
        }
      }
    }
  }


  if (useRep == NULL) // fallback
    useRep = GetLowestRepresentation();

  //std::cerr << "Representation used: " << useRep->GetId() << std::endl;

  //IRepresentation* rep = (this->m_availableRepresentations->begin()->second);
  *usedRepresentation = useRep;
  *requested_segment_number = currentSegmentNumber;
  *hasDownloadedAllSegments = false;
  lastUsedRep = useRep;


  return useRep->GetSegmentList()->GetSegmentURLs().at(currentSegmentNumber++);
}

}

}
