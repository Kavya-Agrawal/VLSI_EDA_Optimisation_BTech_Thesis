// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.99506291;
  double density_weight = 0.30288622;
  double prefix_weight = 0.48288017;
  double neighborhood_weight = 0.06874841;
  double late_weight = 0.16395974;
  double critical_weight = 0.47995767;
  unsigned budget = 27;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
