// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.48304988;
  double density_weight = 0.53856092;
  double prefix_weight = 0.33066846;
  double neighborhood_weight = 0.31686698;
  double late_weight = 0.18841501;
  double critical_weight = 0.29589943;
  unsigned budget = 24;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
